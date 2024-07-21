/*
* File:          Ship.cpp
* Project:       CMSC 202 Project 2, Spring 2021
* Author:        Johnson Xie
*
* Description:   This file contains the Ship class
*                in order to run the Ship functions
*                and Ship variables
*
*/

#include "Ship.h"
 
 Ship::Ship()
 {
    m_shipName = SHIP_NAME;
    m_shipRank = RANK_D;
    m_numMaterials = 0;
 }

 Ship::Ship(string name)
 {
    SetName(name);
 }

 string Ship::GetName()
 {
    return m_shipName;
 }

 void Ship::SetName(string name)
 {
    //if user doesnt enter a ship name, set default name
    if(name.length() == EMPTY_NAME)
    {
        m_shipName = SHIP_NAME;
    }

    else
    {
        m_shipName = name;
    }
 }

 int Ship::CheckMaterial(Material material)
 {
    int index = -1;

    for(int i = 0; i < m_numMaterials; i++)
    {
        if (m_myMaterials[i].m_name == material.m_name)
        {
            index = i;
        }
    }

    return index;
 }

 void Ship::AddMaterial(Material newMaterial)
 {
    newMaterial.m_quantity = 0;
    m_myMaterials[m_numMaterials] = newMaterial;
    m_numMaterials++;
 }
 
 void Ship::IncrementQuantity(Material currMaterial)
 {
    currMaterial.m_quantity++;
 }

 bool Ship::DecrementQuantity(Material currMaterial)
 {
    bool decSuccess = true;
    if(currMaterial.m_quantity == 0)
        {
            decSuccess = false;
        }

    else
    {
        currMaterial.m_quantity--;
    }

    return decSuccess;
 }

 bool Ship::CheckQuantity(Material firstMaterial, Material secondMaterial)
 {
    if(firstMaterial.m_quantity >= 1 && secondMaterial.m_quantity >= 1)
    {
        return true;
    }

    else
    {
        return false;
    }
 }

Material Ship::GetMaterial(int numOfMaterial)
{
    return m_myMaterials[numOfMaterial];
}

void Ship::IncRank()
{
    if(m_shipRank == RANK_D)
        m_shipRank = RANK_C;

    if(m_shipRank == RANK_C)
        m_shipRank = RANK_B;

    if(m_shipRank == RANK_B)
        m_shipRank = RANK_A;

    if(m_shipRank == RANK_A)
        m_shipRank = RANK_S;
    
    if(m_shipRank == RANK_S)
        cout << "Max Rank already reached. " << endl;
}

char Ship::GetRank() 
{
    return m_shipRank;
}
