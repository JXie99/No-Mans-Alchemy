/*
* File:          Game.cpp
* Project:       CMSC 202 Project 2, Spring 2021
* Author:        Johnson Xie
*
* Description:   This file contains the Game class
*                in order to run the Game functions
*                and Game variables
*
*/

#include "Game.h"

Game::Game()
{   
    GameTitle();
    //load all materials and reciepes into m_materials 
    LoadMaterials();

    string name;
    cout << "What would you like the name of your ship to be? " << endl;
    getline(cin, name);
    m_myShip.SetName(name);
    
    //copies all materials from m_materials into ship material array 
    for(int i = 0; i < PROJ2_SIZE; i++)
    {
        m_myShip.AddMaterial(m_materials[i]);   
    }

}

void Game::LoadMaterials()
{
    ifstream myfile(PROJ2_DATA);
    if(myfile.is_open())

    {
        cout << "File has been opened!" << endl;
        for (int i = 0; i < PROJ2_SIZE; i++)
        {
            getline(myfile, m_materials[i].m_name, ',');
            getline(myfile, m_materials[i].m_type, ',');
            getline(myfile, m_materials[i].m_material1, ',');
            getline(myfile, m_materials[i].m_material2);
        }
    }

    else
    {
        cout << "file is not opened" << endl;
    }
}

void Game::StartGame()
{
    int uniqueItems = 0;
    int game = CONTINUE;

    while(uniqueItems != 4)
    {
        int choice = MainMenu();
    
        if(choice == 1)
            DisplayMaterials();
        
        if(choice == 2)
            SearchMaterials();
        
        if(choice == 3)
            CombineMaterials();
        
        if(choice == 4)
            CalcScore();
        
        if(choice == 5)
            cout << "Thank you for playing" << endl;
            uniqueItems = 4;  
            game = QUIT;

         //constantly checks how many total unique items are in array. 
        if(game == CONTINUE)
        {
            for(int i = 0; i < PROJ2_SIZE; i++)
            {
                if(m_myShip.GetMaterial(i).m_type == "unique")
                {
                    if(m_myShip.GetMaterial(i).m_quantity == 1)
                        uniqueItems++;
                }
            }

            if(uniqueItems >= 1)
            {
                cout << "You currently have " << uniqueItems << " unique itmes" << endl;
            }

            if(uniqueItems == 4)
            {
                cout << "Congratz, You win the game!" << endl;
            }

            else
            {
                uniqueItems = 0;
            }
        }
    }
}

void Game::DisplayMaterials()
{
    // displays all possible materials and their quantities 
    for(int i = 0; i < PROJ2_SIZE; i++)
    {
        cout << i + 1 << m_myShip.GetMaterial(i).m_name << ", "; 
        cout << m_myShip.GetMaterial(i).m_quantity << endl;
    }
}

int Game::MainMenu()
{
    int userChoice = 0;

    do
    {
        cout << "What would you like to do?" << endl;
        cout << "1. Display Ship Materials" << endl;
        cout << "2. Search for Raw Materials" << endl;
        cout << "3. Attempt to Merge Materials" << endl;
        cout << "4. See Score" << endl;
        cout << "5. Quit" << endl;
        cin >> userChoice;
    } while (userChoice > 5 and userChoice < 1);

    return userChoice;
}

void Game::SearchMaterials()
{
    int rawMaterialsNum = 0;

    //checks how many raw materials there are
    for(int i = 0; i < PROJ2_SIZE; i++)
    {
        if(m_materials[i].m_type == "raw")
            rawMaterialsNum++;
    }

    //selects a random raw materials' index
    int randRawIndex = rand() % rawMaterialsNum;
    m_myShip.IncrementQuantity(m_materials[randRawIndex]);
    cout << m_myShip.GetMaterial(randRawIndex).m_name << " found!" << endl;

}

void Game::CombineMaterials() 
{
    int choiceOne;
    cout << "What material would you like merge?" << endl;
    cin >> choiceOne;
    RequestMaterial(choiceOne);

    int choiceTwo;
    cout << "What other material would you like to merge? " << endl;
    cin >> choiceTwo;
    RequestMaterial(choiceTwo);

    bool enoughMat = m_myShip.CheckQuantity(m_myShip.GetMaterial(choiceOne), m_myShip.GetMaterial(choiceTwo));

    if (enoughMat == true)
    {
        int theRecipe = SearchRecipes(m_myShip.GetMaterial(choiceOne).m_name, m_myShip.GetMaterial(choiceTwo).m_name);
        if (theRecipe == -2)
        {
            cout << "no recipe found for these two materials" << endl;
        }

        else
        {
            //checks to see if it is a dup unique item
            if(m_myShip.GetMaterial(theRecipe).m_type == "unique" && m_myShip.GetMaterial(theRecipe).m_quantity == 1)
                cout << "You cannot have another copy of this unique material" << endl;
            else 
            {
                //prints success message of material combination
                cout << m_myShip.GetMaterial(choiceOne).m_name << " combined with ";
                cout << m_myShip.GetMaterial(choiceTwo).m_name << " to form ";
                cout << m_myShip.GetMaterial(theRecipe).m_name << endl;

                //increases quantity for specific unique material
                m_myShip.IncrementQuantity(m_myShip.GetMaterial(theRecipe));
                bool materialOneDec = m_myShip.DecrementQuantity(m_myShip.GetMaterial(choiceOne)); //decreases material 1 quantity
                bool materialTwoDec = m_myShip.DecrementQuantity(m_myShip.GetMaterial(choiceTwo)); //decreases material 2 quantity

                if (materialOneDec == true && materialTwoDec == true)
                    cout << "congratulations, you have made the material" << endl;

                if (m_myShip.GetMaterial(theRecipe).m_type == "unique")
                    m_myShip.IncRank();
            }
        }
    }
    else
    {
        cout << "You do not have enough of one of the materials to continue" << endl;
    }

}

void Game::RequestMaterial(int &choice)
{
    while (choice <= -1 || choice > (PROJ2_SIZE)) //62
    {
        if (choice == -1)
            DisplayMaterials();
        cout << "try again -1 to show list" << endl;
        cin >> choice;
    }
    // used to access the correct index of material.
    if(choice != -1)
        choice = choice - 1;

}

int Game::SearchRecipes(string material1, string material2)
{
    for(int i = 0; i < PROJ2_SIZE; i++)
    {
        if(material1 == m_materials[i].m_material1 || material1 == m_materials[i].m_material2)
        {
            if (material2 == m_materials[i].m_material1 || material2 == m_materials[i].m_material2)
            {
                cout << m_materials[i].m_name << endl;
                return i;
            }
        }
    }
    return -2;
}

void Game::CalcScore() 
{
    cout << "The great ship: " << m_myShip.GetName() << endl;
    cout << "Ship Rank: " << m_myShip.GetRank() << endl;
}