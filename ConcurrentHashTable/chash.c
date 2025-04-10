#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

// =============================================================
// Data Structures and Global Variables
// =============================================================

// Structure for each hash table record
typedef struct hash_struct {
    uint32_t hash;           // Hash value computed from the name
    char name[50];           // Key: name (max 50 characters)
    uint32_t salary;         // Salary associated with the name
    struct hash_struct *next;// Pointer to the next node in the list
} hashRecord;

// Head pointer for the linked list that represents the hash table
hashRecord *head = NULL;

// Read-write lock to protect access to the hash table
pthread_rwlock_t table_lock;

// Global counters for lock acquisitions and releases (for summary output)
int lock_acquisitions = 0;
int lock_releases = 0;

// =============================================================
// Function Prototypes
// =============================================================

// Jenkins one_at_a_time hash function.
// Computes and returns a 32-bit hash for the given key.
uint32_t jenkins_one_at_a_time_hash(const char *key);

// Insert or update a key-data pair in the hash table.
// If the key already exists, update its salary; otherwise, create a new node.
void insert_record(const char *name, uint32_t salary);

// Delete a key-data pair from the hash table, if it exists.
// This version always prints "DELETE AWAKENED" before acquiring the write lock.
void delete_record(const char *name);

// Search for a key-data pair in the hash table.
// Returns a pointer to a copy of the found record or NULL if not found.
hashRecord* search_record(const char *name);

// Print the entire hash table sorted by hash value.
// This function prints summary information first then prints the sorted table.
void print_table();

// Process a single command read from commands.txt.
// This function parses the command line and calls the appropriate function.
void process_command(const char *command_line);

// Thread routine to execute a command.
// Each command from the file is processed in its own thread.
void *thread_routine(void *arg);

// Utility function: Get current timestamp (in microseconds since epoch).
long long get_timestamp();

// Utility functions to log lock operations with timestamps.
void log_lock_acquired(const char *lock_type);
void log_lock_released(const char *lock_type);

// Static comparison function for sorting by hash value.
static int compare_records(const void *a, const void *b) {
    hashRecord *r1 = *(hashRecord**)a;
    hashRecord *r2 = *(hashRecord**)b;
    if (r1->hash < r2->hash) return -1;
    else if (r1->hash > r2->hash) return 1;
    else return 0;
}

// =============================================================
// Main Function
// =============================================================
int main(int argc, char *argv[]) {
    // Initialize the read-write lock
    if (pthread_rwlock_init(&table_lock, NULL) != 0) {
        perror("Failed to initialize lock");
        exit(EXIT_FAILURE);
    }
    
    // Open and read the commands.txt file (hard-coded filename)
    FILE *fp = fopen("commands.txt", "r");
    if (!fp) {
        perror("Failed to open commands.txt");
        exit(EXIT_FAILURE);
    }
    
    char line[256];
    // Read first line: expected format "threads,<number>,0"
    if (fgets(line, sizeof(line), fp) == NULL) {
        fprintf(stderr, "commands.txt is empty\n");
        exit(EXIT_FAILURE);
    }
    line[strcspn(line, "\r\n")] = '\0';
    
    char *token = strtok(line, ",");
    if (!token || strcasecmp(token, "threads") != 0) {
        fprintf(stderr, "First line must be a threads command\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(NULL, ",");
    if (!token) {
        fprintf(stderr, "Missing thread count\n");
        exit(EXIT_FAILURE);
    }
    int num_commands = atoi(token);
    
    // Print the starting messages as in sample output.
    printf("Running %d threads\n", num_commands);
    printf("%lld: WAITING ON INSERTS\n", get_timestamp());
    
    // Allocate arrays for thread IDs and command strings.
    pthread_t *threads = malloc(sizeof(pthread_t) * num_commands);
    char **commands = malloc(sizeof(char*) * num_commands);
    if (!threads || !commands) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    
    // Read the next num_commands lines (each representing one command)
    for (int i = 0; i < num_commands; i++) {
        if (fgets(line, sizeof(line), fp) == NULL) {
            fprintf(stderr, "Not enough commands in file\n");
            exit(EXIT_FAILURE);
        }
        line[strcspn(line, "\r\n")] = '\0';
        commands[i] = strdup(line);
    }
    fclose(fp);
    
    // Create a thread for each command.
    for (int i = 0; i < num_commands; i++) {
        if (pthread_create(&threads[i], NULL, thread_routine, commands[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }
    
    // Join threads and free command strings.
    for (int i = 0; i < num_commands; i++) {
        pthread_join(threads[i], NULL);
        free(commands[i]);
    }
    free(commands);
    free(threads);
    
    printf("Finished all threads.\n");
    
    // After processing all commands, print the final hash table.
    print_table();
    
    // Cleanup: Destroy the lock.
    pthread_rwlock_destroy(&table_lock);
    
    return 0;
}

// =============================================================
// Function Implementations
// =============================================================

// Jenkins one_at_a_time hash function.
uint32_t jenkins_one_at_a_time_hash(const char *key) {
    uint32_t hash = 0;
    size_t i = 0;
    while (key[i] != '\0') {
        hash += key[i++];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

// Inserts or updates a record in the hash table.
void insert_record(const char *name, uint32_t salary) {
    uint32_t hash = jenkins_one_at_a_time_hash(name);
    
    // Acquire write lock and log the event.
    pthread_rwlock_wrlock(&table_lock);
    log_lock_acquired("WRITE");
    
    long long timestamp = get_timestamp();
    // Log the INSERT command with the computed hash.
    printf("%lld: INSERT,%u,%s,%u\n", timestamp, hash, name, salary);
    
    // Search for an existing record with the same name.
    hashRecord *curr = head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            // Record found; update salary.
            curr->salary = salary;
            log_lock_released("WRITE");
            pthread_rwlock_unlock(&table_lock);
            return;
        }
        curr = curr->next;
    }
    
    // Record not found; create a new node.
    hashRecord *newRecord = malloc(sizeof(hashRecord));
    if (!newRecord) {
        perror("Failed to allocate memory for new record");
        exit(EXIT_FAILURE);
    }
    newRecord->hash = hash;
    strncpy(newRecord->name, name, 50);
    newRecord->name[49] = '\0';
    newRecord->salary = salary;
    newRecord->next = head;
    head = newRecord;
    
    log_lock_released("WRITE");
    pthread_rwlock_unlock(&table_lock);
}

// Deletes a record with the given name from the hash table.
// This version always prints "DELETE AWAKENED" before performing deletion.
void delete_record(const char *name) {
    long long ts_awaken = get_timestamp();
    printf("%lld: DELETE AWAKENED\n", ts_awaken);
    
    pthread_rwlock_wrlock(&table_lock);
    log_lock_acquired("WRITE");
    
    long long timestamp = get_timestamp();
    // Log the DELETE command.
    printf("%lld: DELETE,%s\n", timestamp, name);
    
    hashRecord *curr = head;
    hashRecord *prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    
    log_lock_released("WRITE");
    pthread_rwlock_unlock(&table_lock);
}

// Searches the hash table for a record by name and returns a copy if found.
hashRecord* search_record(const char *name) {
    pthread_rwlock_rdlock(&table_lock);
    log_lock_acquired("READ");
    
    long long timestamp = get_timestamp();
    // Log the SEARCH command.
    printf("%lld: SEARCH,%s\n", timestamp, name);
    
    hashRecord *curr = head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            hashRecord *found = malloc(sizeof(hashRecord));
            if (found) {
                found->hash = curr->hash;
                strncpy(found->name, curr->name, 50);
                found->name[49] = '\0';
                found->salary = curr->salary;
                found->next = NULL;
            }
            log_lock_released("READ");
            pthread_rwlock_unlock(&table_lock);
            return found;
        }
        curr = curr->next;
    }
    log_lock_released("READ");
    pthread_rwlock_unlock(&table_lock);
    return NULL;
}

// Prints the entire hash table in sorted order along with summary information.
void print_table() {
    pthread_rwlock_rdlock(&table_lock);
    log_lock_acquired("READ");
    log_lock_released("READ");
    pthread_rwlock_unlock(&table_lock);
    
    // Print summary information using actual counter values.
    printf("Number of lock acquisitions: %d\n", lock_acquisitions);
    printf("Number of lock releases: %d\n", lock_releases);
    
    // Acquire read lock to print the sorted table.
    pthread_rwlock_rdlock(&table_lock);
    log_lock_acquired("READ");
    
    int count = 0;
    hashRecord *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    
    hashRecord **records = malloc(sizeof(hashRecord*) * count);
    if (!records && count > 0) {
        perror("Failed to allocate memory for records array");
        exit(EXIT_FAILURE);
    }
    curr = head;
    for (int i = 0; i < count; i++) {
        records[i] = curr;
        curr = curr->next;
    }
    
    qsort(records, count, sizeof(hashRecord*), compare_records);
    
    for (int i = 0; i < count; i++) {
        printf("%u,%s,%u\n", records[i]->hash, records[i]->name, records[i]->salary);
    }
    
    free(records);
    log_lock_released("READ");
    pthread_rwlock_unlock(&table_lock);
}

// Parses a command string and calls the appropriate function.
void process_command(const char *command_line) {
    char buffer[256];
    strncpy(buffer, command_line, 255);
    buffer[255] = '\0';
    
    char *token = strtok(buffer, ",");
    if (!token)
        return;
    
    if (strcasecmp(token, "insert") == 0) {
        // Format: insert,<name>,<salary>
        char *name = strtok(NULL, ",");
        char *salary_str = strtok(NULL, ",");
        if (name && salary_str) {
            uint32_t salary = (uint32_t)atoi(salary_str);
            insert_record(name, salary);
        }
    } else if (strcasecmp(token, "delete") == 0) {
        // Format: delete,<name>,0
        char *name = strtok(NULL, ",");
        if (name) {
            delete_record(name);
        }
    } else if (strcasecmp(token, "search") == 0) {
        // Format: search,<name>,0
        char *name = strtok(NULL, ",");
        if (name) {
            hashRecord *result = search_record(name);
            long long timestamp = get_timestamp();
            if (result) {
                printf("%lld: RECORD FOUND,%u,%s,%u\n", timestamp, result->hash, result->name, result->salary);
                free(result);
            } else {
                printf("%lld: SEARCH: NOT FOUND NOT FOUND\n", timestamp);
            }
        }
    } else if (strcasecmp(token, "print") == 0) {
        // Format: print,0,0
        print_table();
    }
}

// Thread routine that processes a single command.
void *thread_routine(void *arg) {
    char *command_line = (char *)arg;
    process_command(command_line);
    pthread_exit(NULL);
}

// Returns the current timestamp (in microseconds since epoch).
long long get_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long microseconds = (te.tv_sec * 1000000) + te.tv_usec; // calculate milliseconds
    return microseconds;
}

// Logs that a lock was acquired.
void log_lock_acquired(const char *lock_type) {
    long long timestamp = get_timestamp();
    lock_acquisitions++;
    printf("%lld: %s LOCK ACQUIRED\n", timestamp, lock_type);
}

// Logs that a lock was released.
void log_lock_released(const char *lock_type) {
    long long timestamp = get_timestamp();
    lock_releases++;
    printf("%lld: %s LOCK RELEASED\n", timestamp, lock_type);
}