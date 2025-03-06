// Caleb Atchison
// Exam 2 Question 1

interface WeLoveCOP4020 {
    showJobTitle(): void;
    showDescription(): void;
    showYearlySalary(): void;
}

class Barista implements WeLoveCOP4020 {
    showJobTitle(): void {
        console.log("I am a Barista");
    }
    showDescription(): void {
        console.log("I make people happy by giving them the elixer of life: coffee.");
    }
    showYearlySalary(): void {
        console.log("I make about $25,000 per year.");
    }
}

class SoftwareEngineer implements WeLoveCOP4020 {
    showJobTitle(): void {
        console.log("I am a Software Engineer");
    }
    showDescription(): void {
        console.log("I solve problems by developing software.");
    }
    showYearlySalary(): void {
        console.log("I make about $100,000 per year.");
    }
}

class PsychologyMajor implements WeLoveCOP4020 {
    showJobTitle(): void {
        console.log("I am a Psychology Major");
    }
    showDescription(): void {
        console.log("I get any job I can find.");
    }
    showYearlySalary(): void {
        console.log("I make about $45,000 per year.");
    }
}

const barista = new Barista();
barista.showJobTitle();
barista.showDescription();
barista.showYearlySalary();

const engineer = new SoftwareEngineer();
engineer.showJobTitle();
engineer.showDescription();
engineer.showYearlySalary();

const psychMajor = new PsychologyMajor();
psychMajor.showJobTitle();
psychMajor.showDescription();
psychMajor.showYearlySalary();