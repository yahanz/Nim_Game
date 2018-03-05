/*
 File: subtraction.cpp
 Created by: Yahan Zhang
 Creation Date: 11.10.2014
 Synopsis: This program is for playing a variation of the Subtraction game called the game of NIM.
 */

#include <iostream>
#include <iomanip>
using namespace std;

// FUNCTION PROTOTYPES:
int read_rods (const int RODS);
void procedure (int array[],int size,const int OBJECTS);
void draw_rods (int array[],int size);
void draw_rods1(int array_index,int number_of_objects,int sum);
void statistics (int array[],int size);
void smallest (int array[],int size);
void largest (int array[],int size);
void average (int array[],int size);
bool all_zero (const int array[],int size);
void next_move (int array[],int size,int player,int & rod_chosen,int & objects_removed);
int choose_rod (int player);
void validate_rod (int player,int & rod_chosen,int size);
void validate_rod1 (int array[],int player,int & rod_chosen);
int numofobjects_to_remove (int objects,int rod_chosen);
void validate_objects (int array[],int rod_chosen,int & objects_removed,int objects);
void move_objects (int array[],int rod_chosen,int objects_removed);
void congrats (int player);
void switch_the_turn (int & player);

int main()
{
    const int RODS(15);
    const int OBJECTS(10);
    int * array;
    int number_of_rods(1);
    int player(1);
    int rod_chosen;
    int objects_removed;
    bool allzero(false);
    // Algorithm:
    // Prompt and read number of rods
    number_of_rods=read_rods (RODS);
    // Prompt and read the number of objects in each rod
    array=new int [number_of_rods];
    procedure (array,number_of_rods,OBJECTS);
    // Draw the rods with percentages
    draw_rods (array,number_of_rods);
    // Display statistics
    statistics (array,number_of_rods);
    // WHILE some rod is NOT empty DO
    while (!allzero)
    {
        // Prompt and read the next player's move
        next_move (array,number_of_rods,player,rod_chosen,objects_removed);
        // Remove the specified number of objects from the specified rod
        move_objects (array,rod_chosen,objects_removed);
        // IF all the heaps are empty, THEN
        allzero=all_zero (array,number_of_rods);
        if(allzero)
        {
            // Print a message congratulating the winning player.
            congrats (player);
        }
        // ELSE
        else
        {
            // Redraw the rods with percentages
            draw_rods (array,number_of_rods);
            // Display statistics
            statistics (array,number_of_rods);
            // Change to the other player
            switch_the_turn (player);
            // END IF
        }
        // END WHILE
    }
    delete [] array;
    return 0;
}

// FUNCTION DEFINITIONS:
/*
 This function prompts the user for the number of rods used in the game and checks whether the number entered is between 1 and the maximum number of rods.
 RODS is the maximum number of rods.
 */
int read_rods (const int RODS)
{
    int rods;
    cout<<"How many rods are in this game? ";
    cin>>rods;
    while (rods<1 || rods>RODS)
    {
        cout<<"Number of rods must be positive and less than or equal to "<<RODS<<endl;
        cout<<"Enter number of rods again: ";
        cin>>rods;
    }
    cout<<endl;
    return (rods);
}

/*
 This function prompts the user for the number of objects to place on this rod and checks whether the number of objects entered for the rod is between 1 and the maximum number of objects allowed.
 array[] is the array of rods.
 size is the size of the array.
 OBJECTS is the maximum number of objects per rod.
 */
void procedure (int array[],int size,const int OBJECTS)
{
    int n;
    for (int i=0;i<size;i++)
    {
        cout<<"How many objects are on rod "<<i<<": ";
        cin>>n;
        while (n<1||n>OBJECTS)
        {
            cout<<"Sorry, the number of objects must be positive and less than or equal to "<<OBJECTS<<"."<<endl;
            cout<<"How many objects are on rod "<<i<<": ";
            cin>>n;
        }
        array[i]=n;
    }
}

/*
 This function calculates the total number of objects in the array of rods and traverses the array of rods and calls a helper procedure to display each complete row.
 array[] is the array of rods.
 size is the size of the array.
 */
void draw_rods (int array[],int size)
{
    int sum(0);
    for (int i=0;i<size;i++)
    {
        sum=sum+array[i];
    }
    cout<<endl;
    for (int i=0;i<size;i++)
    {
        draw_rods1 (i,array[i],sum);
    }
    cout<<endl;
}

/*
 This function displays each complete row.
 array_index is the array index for this rod.
 number_of_objects is the number of objects for this rod.
 sum is the total number of objects in the array of rods.
 */
void draw_rods1(int array_index,int number_of_objects,int sum)
{
    cout<<"Rod"<<setw(3)<<array_index<<": ";
    for (int x=0;x<number_of_objects;x++)
    {
        cout<<"#";
    }
    double percentage=number_of_objects*100.00/sum;
    cout<<setw(16-number_of_objects)<<"("<<fixed<<setprecision(3)<<percentage<<"%)"<<endl;
}

/*
 This function displays the statistics for the list of rods.
 The statistics are 1) The rods with the smallest number of objects, 2) The rods with the largest number of objects, and 3) The average number of objects per rod taking into account only rods with objects.
 array[] is the array of rods.
 size is the size of the array.
 */
void statistics (int array[],int size)
{
    smallest (array,size);
    largest (array,size);
    average (array,size);
    cout<<endl;
}

/*
 This function displays the rods with the smallest number of objects.
 array[] is the array of rods.
 size is the size of the array.
 */
void smallest (int array[],int size)
{
    int smallest=array[0];
    if (array[0]==0)
    {
        for (int i=1;i<size;i++)
        {
            if (array[i]!=0)
            {
                smallest=array[i];
            }
        }
    }
    for (int i=1;i<size;i++)
    {
        if (array[i]!=0 && array[i]<smallest)
        {
            smallest=array[i];
        }
    }
    for (int i=0;i<size;i++)
    {
        if (array[i]==smallest)
        {
            cout<<"Rod "<<i<<" has the smallest number of objects with "<<smallest<<" object(s)."<<endl;
        }
    }
}

/*
 This function displays the rods with the largest number of objects.
 array[] is the array of rods.
 size is the size of the array.
 */
void largest (int array[],int size)
{
    int largest=array[0];
    for (int i=1;i<size;i++)
    {
        if (array[i]>largest)
        {
            largest=array[i];
        }
    }
    for (int i=0;i<size;i++)
    {
        if (array[i]==largest)
        {
            cout<<"Rod "<<i<<" has the largest number of objects with "<<largest<<" object(s)."<<endl;
        }
    }
}

/*
 This function displays the average number of objects per rod taking into account only rods with objects.
 array[] is the array of rods.
 size is the size of the array.
 */
void average (int array[],int size)
{
    int sum(0);
    int rods_with_object(0);
    for (int i=0;i<size;i++)
    {
        if (array[i]!=0)
        {
            sum=sum+array[i];
            rods_with_object++;
        }
    }
    double average=sum*1.00/rods_with_object;
    cout<<"The average number of objects per rod (i.e., rods with objects) is "<<fixed<<setprecision(2)<<average<<" objects."<<endl;
}

/*
 This function returns true if all the rods have zero object and returns false otherwise.
 array[] is the array of rods.
 size is the size of the array.
 */
bool all_zero (const int array[],int size)
{
    bool zero=true;
    int rods_without_objects(0);
    for (int i=0;i<size;i++)
    {
        if (array[i]==0)
        {
            rods_without_objects++;
        }
    }
    if (rods_without_objects!=size)
    {
        zero=false;
    }
    if (zero)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

/*
 This function implements step (vi) of the algorithm where the current player makes her next move.
 array[] is the array of rods.
 size is the size of the array.
 player is the player id.
 rod_chosen is the rod chosen by the player on this turn.
 objects_removed is the number of objects the player would like to remove.
 */
void next_move (int array[],int size,int player,int & rod_chosen,int & objects_removed)
{
    rod_chosen=choose_rod (player);
    validate_rod (player,rod_chosen,size);
    validate_rod1 (array,player,rod_chosen);
    objects_removed=numofobjects_to_remove (array[rod_chosen],rod_chosen);
    validate_objects (array,rod_chosen,objects_removed,array[rod_chosen]);
}

/*
 This function prompts the player to choose a rod (rod id) and then returns this value.
 player is the player id.
 */
int choose_rod (int player)
{
    int rod_id;
    cout<<"Player ("<<player<<") : Which rod would you like to play? ";
    cin>>rod_id;
    return (rod_id);
}

/*
 This function validates the rod selected by this player, i.e., the rod selected must be between 0 and n-1 where n is the total number of rods.
 player is the player id.
 rod_chosen is the rod selected by this player.
 size is the total number of rods.
 */
void validate_rod (int player,int & rod_chosen,int size)
{
    while(rod_chosen<0||rod_chosen>size-1)
    {
        cout<<"Invalid rod number. Please try again."<<endl;
        rod_chosen=choose_rod (player);
    }
}

/*
 This function validates whether the rod selected has at least one object.
 array[] is the array of rods.
 player is the player id.
 rod_chosen is the rod selected by this player.
 */
void validate_rod1 (int array[],int player,int & rod_chosen)
{
    while(array[rod_chosen]==0)
    {
        cout<<"Rod "<<rod_chosen<<" has zero objects. Please select a different rod."<<endl;
        rod_chosen=choose_rod (player);
    }
}

/*
 This function prompts and reads how many objects to remove from the chosen rod.
 objects is the number of objects to remove from the chosen rod.
 rod_chosen is the rod selected by this player.
 */
int numofobjects_to_remove (int objects,int rod_chosen)
{
    int num;
    cout<<"Enter number of objects to remove ("<<objects<<" or less) from rod "<<rod_chosen<<": ";
    cin>>num;
    return (num);
}

/*
 This function validates whether the number of objects to remove is positive and does not exceed the number of objects on the chosen rod.
 array[] is the array of rods.
 rod_chosen is the rod selected by this player.
 objects_removed is the number of objects the player would like to remove.
 objects is the number of objects in the rod.
 */
void validate_objects (int array[],int rod_chosen,int & objects_removed,int objects)
{
    while(objects_removed<1||objects_removed>objects)
    {
        if(objects_removed<1)
        {
            cout<<"Number of objects you can remove must be positive. Try again."<<endl;
        }
        if(objects_removed>objects)
        {
            cout<<"Can only remove up to "<<objects<<" object(s). Please try again."<<endl;
        }
        objects_removed=numofobjects_to_remove (array[rod_chosen],rod_chosen);
    }
}

/*
 This function modifies the array of rods by subtracting the specified number of objects from the chosen rod.
 array[] is the array of rods.
 rod_chosen is the rod id of the chosen rod.
 objects_removed is the number of objects to remove.
 */
void move_objects (int array[],int rod_chosen,int objects_removed)
{
    array[rod_chosen]=array[rod_chosen]-objects_removed;
}

/*
 This function prints a message congratulating the winning player.
 player is the player id.
 */
void congrats (int player)
{
    cout<<endl;
    cout<<"Congratulations! Player "<<player<<" wins."<<endl;
}

/*
 This function switches the turn to the other player.
 player is the player id.
 */
void switch_the_turn (int & player)
{
    if(player==1)
    {
        player=2;
    }
    else
    {
        player=1;
    }
}
