#include "CompanyField.h"
#include "Player.h"
#include "Monopoly.h"

CompanyField::CompanyField(const MyString& name, size_t companyPrice, int boardIndex)
	: Field(boardIndex,name)
{
	this->companyPrice = companyPrice;
}

size_t CompanyField::getCompanyPrice() const
{
	return companyPrice;
}

int CompanyField::getOwnerId() const
{
	return ownerId;
}

int CompanyField::getUtilityCount() const
{
	return utilityCount;
}

int CompanyField::getRentPrice() const
{
    int rent = Monopoly::getInstance()->getPlayerOnTurn().getLastRoll();
    if (utilityCount == 1)
    {
        rent *= 4; 
    }
    else if (utilityCount == 2)
    {
        rent *= 10; 
    }
	return rent;
}

void CompanyField::setUtilityCount(int level) 
{
	utilityCount = level;
}

void CompanyField::ApplyAction(Player& player)
{
    std::cout << "\n>>> You landed on: " << getName() << " <<<" << std::endl;

    if (ownerId == -1)
    {
        std::cout << "This company is unowned." << std::endl;
        std::cout << "You can buy it for " << companyPrice << "$." << std::endl;
        std::cout << "Your current balance: $" << player.getMoney() << std::endl;

        if (player.getMoney() >= companyPrice)
        {
            std::cout << "Do you want to buy this station? (y/n): ";
            char choice;
            std::cin >> choice;

            if (choice == 'y' || choice == 'Y')
            {
                ownerId = player.getPlayerId();
                player.addUtility(this);
                std::cout << "You bought " << getName() << " successfully!" << std::endl;
            }
            else {
                std::cout << "You chose not to buy the company." << std::endl;
            }
        }
        else {
            std::cout << "You do not have enough money to buy this company." << std::endl;
        }

    }
    else if (ownerId != player.getPlayerId())
    {
        std::cout << "This company is owned by Player " << ownerId << "." << std::endl;

		int rent =getRentPrice();
        std::cout << "You must pay rent of " << rent << "$ ." << std::endl;;

        if (player.getMoney() >= rent)
        {
            player.subtractMoney(rent);

            Player& ownerOfProperty = Monopoly::getInstance()->getPlayer(ownerId);
            ownerOfProperty.addMoney(rent);

            std::cout << "You paid " << rent << "$ rent to Player " << ownerOfProperty.getPlayerName() << "." << std::endl;
        }
        else
        {
            std::cout << "You do not have enough money to pay the rent!" << std::endl;
        }

    }
    else
    {
        std::cout << "You have landed on your company. Relax and see sth about OOP." << std::endl;
    }
	 
}

Field* CompanyField::clone() const
{
	return new CompanyField(*this);
}
