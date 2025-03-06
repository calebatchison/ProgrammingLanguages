// Caleb Atchison
// Exam 2 Question 3

interface ReesesCandy {
    getDescription(): string;
}
  
class ReesePieces implements ReesesCandy {
    getDescription(): string {
        return "Reese's Pieces: Crunchy, peanut butter candy pieces that ET adored during his visit to Eatth.";
    }
}
  
class ReeseCups implements ReesesCandy {
    getDescription(): string {
        return "Reese's Cups: The classic peanut butter cup.";
    }
}
  
class ReeseKingSize implements ReesesCandy {
    getDescription(): string {
        return "Reese's King Size Cups: A larger version for those who are extra indulgent.";
    }
}
  
enum CandyType {
    Pieces = "pieces",
    Cups = "cups",
    KingSize = "kingsize"
}
  
class ReesesCandyFactory {
    static createCandy(type: CandyType): ReesesCandy {
        switch (type) {
            case CandyType.Pieces:
                return new ReesePieces();
            case CandyType.Cups:
                return new ReeseCups();
            case CandyType.KingSize:
                return new ReeseKingSize();
            default:
                throw new Error("Unknown candy type");
        }
    }
}
  
const candyTypes: CandyType[] = [CandyType.Pieces, CandyType.Cups, CandyType.KingSize];

    candyTypes.forEach(type => {
    const candy = ReesesCandyFactory.createCandy(type);
    console.log(candy.getDescription());
});