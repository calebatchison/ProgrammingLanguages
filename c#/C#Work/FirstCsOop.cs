using System;
using System.Collections.Generic;
using System.Linq;

namespace FirstCSOop
{
    // Part 1: Base class and derived classes for Animals
    public class Animal
    {
        public void move() { Console.WriteLine("Animal is moving"); }
        public void sleep() { Console.WriteLine("Animal is sleeping"); }
        public void eat() { Console.WriteLine("Animal is eating"); }
    }

    public class Dog : Animal
    {
        public void sing() { Console.WriteLine("Dog is singing"); }
        public void wash() { Console.WriteLine("Dog is being washed"); }
        public void turnAround() { Console.WriteLine("Dog turned around"); }
    }

    public class Cat : Animal
    {
        public void sing() { Console.WriteLine("Cat is singing"); }
        public void wash() { Console.WriteLine("Cat is being washed"); }
        public void turnAround() { Console.WriteLine("Cat turned around"); }
    }

    public class Bird : Animal
    {
        public void sing() { Console.WriteLine("Bird is singing"); }
        public void wash() { Console.WriteLine("Bird is being washed"); }
        public void turnAround() { Console.WriteLine("Bird turned around"); }
    }

    // Part 2: IUFO interface and implementing classes
    public interface IUFO
    {
        void fly();
        void goToHyperspace();
        void land();
    }

    public class SmallCraft : IUFO
    {
        public void fly() { Console.WriteLine("SmallCraft is flying"); }
        public void goToHyperspace() { Console.WriteLine("SmallCraft is going to hyperspace"); }
        public void land() { Console.WriteLine("SmallCraft is landing"); }
    }

    public class LargeCraft : IUFO
    {
        public void fly() { Console.WriteLine("LargeCraft is flying"); }
        public void goToHyperspace() { Console.WriteLine("LargeCraft is going to hyperspace"); }
        public void land() { Console.WriteLine("LargeCraft is landing"); }
    }

    public class BossCraft : IUFO
    {
        public void fly() { Console.WriteLine("BossCraft is flying"); }
        public void goToHyperspace() { Console.WriteLine("BossCraft is going to hyperspace"); }
        public void land() { Console.WriteLine("BossCraft is landing"); }
    }

    // Part 1 Filtering: Problem1
    public class Problem1
    {
        public static IEnumerable<int> myFilter(IEnumerable<int> input)
        {
            return input.Where(x => !(x % 5 == 0 && x > 50))
                        .Select(x => x * x * x)
                        .Where(x => x % 2 != 0);
        }
    }

    // Part 2 Filtering: Problem2
    public class Problem2
    {
        public static IEnumerable<int> myFilter(IEnumerable<int> input)
        {
            return input.Where(x => !(x % 6 == 0 && x < 42))
                        .Select(x => x * x)
                        .Where(x => x % 2 == 0);
        }
    }

    // Part 3 Merging: TestProblem2
    public class TestProblem2
    {
        public static IEnumerable<int> merge(IEnumerable<int> input1,
                                               IEnumerable<int> input2,
                                               IEnumerable<int> input3,
                                               IEnumerable<int> input4)
        {
            // Return numbers that are present in all four lists and are multiples of 10
            return input1.Intersect(input2)
                         .Intersect(input3)
                         .Intersect(input4)
                         .Where(x => x % 10 == 0);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            // Part 1: Instantiate Animal derived classes and call their methods
            Dog dog = new Dog();
            Cat cat = new Cat();
            Bird bird = new Bird();

            dog.move(); dog.sleep(); dog.eat(); dog.sing(); dog.wash(); dog.turnAround();
            cat.move(); cat.sleep(); cat.eat(); cat.sing(); cat.wash(); cat.turnAround();
            bird.move(); bird.sleep(); bird.eat(); bird.sing(); bird.wash(); bird.turnAround();

            Console.WriteLine("----------");

            // Part 2: Instantiate IUFO implementations and call their methods
            SmallCraft smallCraft = new SmallCraft();
            LargeCraft largeCraft = new LargeCraft();
            BossCraft bossCraft = new BossCraft();

            smallCraft.fly(); smallCraft.goToHyperspace(); smallCraft.land();
            largeCraft.fly(); largeCraft.goToHyperspace(); largeCraft.land();
            bossCraft.fly(); bossCraft.goToHyperspace(); bossCraft.land();

            Console.WriteLine("----------");

            // Part 1 Filtering Problem (Problem1)
            Random rnd1 = new Random(5); // Seed for repeatability
            var listForProblem1 = Enumerable.Range(1, 100).Select(i => rnd1.Next() % 101);
            var answer1 = Problem1.myFilter(listForProblem1);
            foreach (int i in answer1)
            {
                Console.WriteLine(i);
            }

            Console.WriteLine("----------");

            // Part 2 Filtering Problem (Problem2)
            Random rnd2 = new Random();
            var listForProblem2 = Enumerable.Range(1, 100).Select(i => rnd2.Next() % 101);
            var answer2 = Problem2.myFilter(listForProblem2);
            foreach (int i in answer2)
            {
                Console.WriteLine(i);
            }

            Console.WriteLine("----------");

            // Part 3 Merging Problem (TestProblem2)
            var list1 = Enumerable.Range(1, 15);
            var list2 = Enumerable.Range(1, 21).Select(x => 2 * x);
            var list3 = Enumerable.Range(0, 10).Select(x => 3 + 2 * x); // Generates odds: 3, 5, ..., 21
            var list4 = Enumerable.Range(1, 21).Select(x => 5 * x);
            var answer3 = TestProblem2.merge(list1, list2, list3, list4);
            foreach (int i in answer3)
            {
                Console.WriteLine(i);
            }
        }
    }
}
