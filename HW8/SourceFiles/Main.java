import java.util.Scanner;

/**
 * This class is the main class of homework 8.
 *
 * @author Harun Albayrak
 * @version 1.0 January,2020.
 */
public class Main {
    /**
     * the main of the homework 8.
     *
     * @param args the input arguments
     */
    public static void main(String[] args) {

        Character repeat;
        Scanner input = new Scanner(System.in);
        do {
            testFunction();
            System.out.println("Do you want to repeat? (Y : Yes) / (N : No)");
            repeat = input.next().charAt(0);
            while(repeat != 'Y' && repeat != 'y' && repeat != 'N' && repeat != 'n'){
                System.out.println("Wrong input. Try again...");
                repeat = input.next().charAt(0);
            }
        }while(repeat == 'Y' || repeat == 'y');

    }

    /**
     * Test function.
     */
    public static void testFunction(){
        int choice=0;
        Scanner input = new Scanner(System.in);
        System.out.println("***This is the Test Function***");
        System.out.println("* Press 1 : TEST GTUSET       *");
        System.out.println("* Press 2 : TEST GTUVECTOR    *");
        System.out.println("* Press 3 : QUIT              *");
        do{
            choice = input.nextInt();
            input.nextLine();
            if(choice < 1 || choice > 3)
                System.out.println("Wrong input. Try again...");
        }while(choice < 1 || choice > 3);
        switch (choice){
            case 1:
                testSet();
                break;
            case 2:
                testVector();
                break;
            case 3:
                System.exit(1);
                break;
        }
    }

    /**
     * Test function of the set.
     */
    private static void testSet() {
        int choice=0;
        int choiceSize=0;
        String[] testStringArray = {"test1","test2","test3","test4","test5"}; // If you want to add array, then add with testString.insertArray(testStringArray);
        Integer[] testIntegerArray = {33,99,-12,-5,8,0,2,1}; // If you want to add array, then add with testInteger.insertArray(testIntegerArray);
        Character[] testCharacterArray = {'g','T','u','h','a','r','u','N'}; // If you want to add array, then add with testCharacter.insertArray(testCharacterArray);
        Scanner input = new Scanner(System.in);
        System.out.println("* Press 1 : TEST with String    *");
        System.out.println("* Press 2 : TEST with Integer   *");
        System.out.println("* Press 3 : TEST with Character *");
        do{
            choice = input.nextInt();
            input.nextLine();
            if(choice < 1 || choice > 3)
                System.out.println("Wrong input. Try again...");
        }while(choice < 1 || choice > 3);
        switch (choice){
            case 1:
                GTUSet<String> testString = new GTUSet<>();
                System.out.println("How many elements do you want to add?");
                choiceSize = input.nextInt();
                input.nextLine();
                for(int i=0;i<choiceSize;++i){
                    System.out.println("Enter the element you want to add: ");
                    String string = input.nextLine();
                    testString.insert(string);
                }
                System.out.println("Printing container with iterator...");
                GTUIterator<String> itr = testString.iterator();
                while (itr.hasNext())
                    System.out.print(itr.next() + " ");
                System.out.println();
                System.out.println("Size : " + testString.size());
                System.out.println("Max Size : " + testString.max_size());
                if(testString.empty())
                    System.out.println("Test container is empty.");
                else
                    System.out.println("Test container is not empty.");

                if(testString.contains("HarunAlbayrak"))
                    System.out.println("Test container has 'HarunAlbayrak'");
                else
                    System.out.println("Test container has not 'HarunAlbayrak'");

                break;
            case 2:
                GTUSet<Integer> testInteger = new GTUSet<>();
                System.out.println("How many elements do you want to add?");
                choiceSize = input.nextInt();
                input.nextLine();
                for(int i=0;i<choiceSize;++i){
                    System.out.println("Enter the element you want to add: ");
                    Integer integer = input.nextInt();
                    testInteger.insert(integer);
                }

                System.out.println("Printing container with iterator...");
                GTUIterator<Integer> itr2 = testInteger.iterator();
                while (itr2.hasNext())
                    System.out.print(itr2.next() + " ");
                System.out.println();
                System.out.println("Size : " + testInteger.size());
                System.out.println("Max Size : " + testInteger.max_size());
                if(testInteger.empty())
                    System.out.println("Test container is empty.");
                else
                    System.out.println("Test container is not empty.");

                if(testInteger.contains(15))
                    System.out.println("Test container has '15'");
                else
                    System.out.println("Test container has not '15'");

                break;
            case 3:
                GTUSet<Character> testCharacter = new GTUSet<>();
                System.out.println("How many elements do you want to add?");
                choiceSize = input.nextInt();
                input.nextLine();
                for(int i=0;i<choiceSize;++i){
                    System.out.println("Enter the element you want to add: ");
                    Character character = input.next().charAt(0);
                    testCharacter.insert(character);
                }

                System.out.println("Printing container with iterator...");
                GTUIterator<Character> itr3 = testCharacter.iterator();
                while (itr3.hasNext())
                    System.out.print(itr3.next() + " ");
                System.out.println();
                System.out.println("Size : " + testCharacter.size());
                System.out.println("Max Size : " + testCharacter.max_size());
                if(testCharacter.empty())
                    System.out.println("Test container is empty.");
                else
                    System.out.println("Test container is not empty.");

                if(testCharacter.contains('A'))
                    System.out.println("Test container has 'A'");
                else
                    System.out.println("Test container has not 'A'");

                break;
        }
    }

    /**
     * Test function of the vector.
     */
    private static void testVector() {
        int choice=0;
        int choiceSize=0;
        String[] testStringArray = {"test1","test2","test3","test4","test5"}; // If you want to add array, then add with testString.insertArray(testStringArray);
        Integer[] testIntegerArray = {33,99,-12,-5,8,0,2,1}; // If you want to add array, then add with testInteger.insertArray(testIntegerArray);
        Character[] testCharacterArray = {'g','T','u','h','a','r','u','N'}; // If you want to add array, then add with testCharacter.insertArray(testCharacterArray);
        Scanner input = new Scanner(System.in);
        System.out.println("* Press 1 : TEST with String    *");
        System.out.println("* Press 2 : TEST with Integer   *");
        System.out.println("* Press 3 : TEST with Character *");
        do{
            choice = input.nextInt();
            input.nextLine();
            if(choice < 1 || choice > 3)
                System.out.println("Wrong input. Try again...");
        }while(choice < 1 || choice > 3);
        switch (choice){
            case 1:
                GTUVector<String> testString = new GTUVector<>();
                System.out.println("How many elements do you want to add?");
                choiceSize = input.nextInt();
                input.nextLine();
                for(int i=0;i<choiceSize;++i){
                    System.out.println("Enter the element you want to add: ");
                    String string = input.nextLine();
                    testString.insert(string);
                }
                System.out.println("Printing container with iterator...");
                GTUIterator<String> itr = testString.iterator();
                while (itr.hasNext())
                    System.out.print(itr.next() + " ");
                System.out.println();
                System.out.println("Size : " + testString.size());
                System.out.println("Max Size : " + testString.max_size());
                if(testString.empty())
                    System.out.println("Test container is empty.");
                else
                    System.out.println("Test container is not empty.");

                if(testString.contains("HarunAlbayrak"))
                    System.out.println("Test container has 'HarunAlbayrak'");
                else
                    System.out.println("Test container has not 'HarunAlbayrak'");

                break;
            case 2:
                GTUVector<Integer> testInteger = new GTUVector<>();
                System.out.println("How many elements do you want to add?");
                choiceSize = input.nextInt();
                input.nextLine();
                for(int i=0;i<choiceSize;++i){
                    System.out.println("Enter the element you want to add: ");
                    Integer integer = input.nextInt();
                    testInteger.insert(integer);
                }

                System.out.println("Printing container with iterator...");
                GTUIterator<Integer> itr2 = testInteger.iterator();
                while (itr2.hasNext())
                    System.out.print(itr2.next() + " ");
                System.out.println();
                System.out.println("Size : " + testInteger.size());
                System.out.println("Max Size : " + testInteger.max_size());
                if(testInteger.empty())
                    System.out.println("Test container is empty.");
                else
                    System.out.println("Test container is not empty.");

                if(testInteger.contains(15))
                    System.out.println("Test container has '15'");
                else
                    System.out.println("Test container has not '15'");

                break;
            case 3:
                GTUVector<Character> testCharacter = new GTUVector<>();
                System.out.println("How many elements do you want to add?");
                choiceSize = input.nextInt();
                input.nextLine();
                for(int i=0;i<choiceSize;++i){
                    System.out.println("Enter the element you want to add: ");
                    Character character = input.next().charAt(0);
                    testCharacter.insert(character);
                }

                System.out.println("Printing container with iterator...");
                GTUIterator<Character> itr3 = testCharacter.iterator();
                while (itr3.hasNext())
                    System.out.print(itr3.next() + " ");
                System.out.println();
                System.out.println("Size : " + testCharacter.size());
                System.out.println("Max Size : " + testCharacter.max_size());
                if(testCharacter.empty())
                    System.out.println("Test container is empty.");
                else
                    System.out.println("Test container is not empty.");

                if(testCharacter.contains('A'))
                    System.out.println("Test container has 'A'");
                else
                    System.out.println("Test container has not 'A'");

                break;
        }
    }
}
