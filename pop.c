/*
# pop.c
# 2022-03-03
# Nicholas Pasqualino Messere
# Purpose: To simulate the usage and displays of a pop machine for customer and maintenance usage.
# I used the built-in boolean library so I could clearly and reasonably traverse through my program and maintain a good and clear control structure. I needed to define <stdbool.h> at the
# start of my program and this allowed me to use the boolean libraries for c.
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MIN_PRICE 30
#define MAX_PRICE 105
#define NICKEL 5
#define DIME 10
#define PENTE 20
#define NUM_ARGS 2
#define PRICE_MULTIPLE 5
int main (int argc, char *argv[])
{
    bool customer_ready = true;
    int price = 0;
    if (argc < NUM_ARGS || argc > NUM_ARGS)
    {
        printf("Please specify selling price as a command line argument.\nUsage: pop [price]\n");
        customer_ready = false;
    }
    else {
        price = atoi(argv[1]);
        if (price < MIN_PRICE || price > MAX_PRICE)
        {
            printf("Price must be from %i to %i centimes inclusive\n", MIN_PRICE, MAX_PRICE);
            customer_ready = false;
        }

        else {

            if (price % PRICE_MULTIPLE != 0)
            {
                printf("Price must be a multiple of %i.\n", PRICE_MULTIPLE);
                customer_ready = false;

            }
        }

    }


    if (customer_ready)
    {
        printf("Welcome to my C Pop Machine!");
        bool customer_service = true;
        bool show_instructions = true;
        int coin_count = 0; /* Variable which keeps track of how many centimes the user has inputted into the machine */
        bool give_change = false;
        bool shutdown = false;
        bool change_version; /* If the chaange version is false that means the amount of change being given is based on the amount the user has inserted and if true it is based on how much extra the user
                             inputted after the pop has been paid for and dispensed */
        while (customer_service)
        {
            if(show_instructions) /* Display instructions only when the price for pop is set and after soda was dispensed */
            {
                printf("Pop is %d centimes. Please insert any combination of nickels [N\nor n], dimes [D or d] or Pentes [P or p]. You can also press R\nor r for coin return.\n", price);
                show_instructions = false; /* Set instructions boolean variable to false after displaying the message */
            }

            char temp_coin; /* This char variable temp_coin houses the char inputted by the user below */
            printf("Enter coin (NDPR): ");
            scanf(" %c", &temp_coin);
            if (temp_coin == 'N' || temp_coin == 'n' || temp_coin == 'D' || temp_coin == 'd' || temp_coin == 'P' || temp_coin == 'p' || temp_coin == 'R' || temp_coin == 'r' || temp_coin == 'E' || temp_coin == 'e')
            {
                if (temp_coin == 'N' || temp_coin == 'n')
                {
                    printf("   Nickel detected.\n");
                    coin_count = coin_count + NICKEL;

                }

                if (temp_coin == 'D' || temp_coin == 'd')
                {
                    printf("   Dime detected.\n");
                    coin_count = coin_count + DIME;
                }
                if (temp_coin == 'P' || temp_coin == 'p')
                {
                    printf("   Pente detected.\n");
                    coin_count = coin_count + PENTE;
                }

                if (temp_coin == 'R' || temp_coin == 'r')
                {
                    give_change = true; /* Since we are returning the amount inserted, set give_change to true to ignore the amount inserted and go straight to giving back change */
                    show_instructions = true;
                    change_version = false; /* Giving back whatever amount the user inserted */
                }

                if (temp_coin == 'E' || temp_coin == 'e')
                {
                    give_change = true; /* Since we are shutting down the machine and going into maintenance set give_change to true to go straight to giving back the amount inserted into the macchine*/
                    shutdown = true;
                    change_version = false; /*Giving back whatever amount the user input into the machine */
                }

            }
            else {
                   printf("   Unknown coin rejected.\n");

            }

            if (give_change == false) /* While give_change is false keep displaying how much the user has inserted and how much more they need if necessary */
            {
                printf("     You have inserted a total of %d centimes.\n", coin_count);
                if (price - coin_count > 0) /* Check to see if the user has not inserted enough coins to buy pop and if so display a message to insert x amount more */
                {
                    printf("     Please insert %d more centimes.\n", price - coin_count);
                }
            }

            if (coin_count >= price) /* If the amount inserted is greater than or equal to the price we dispense the pop and give any change back, show the instructions and set change version to true*/
            {
                printf("     Pop is dispensed. Thank you for your business! Please come again.\n");
                give_change = true;
                show_instructions = true;
                change_version = true; /* We are going to give back the change depedning on how much the user overpaid for their drink if they even did */

            }

            if (give_change)
            {
                int change_amount;
                int dime_amount = 0; /* Set default coin return amount for dimes to 0 */
                int nickel_amount = 0; /* Set default coin return amount for nickels to 0 */
                if (change_version) /* If the change_version boolean variable is true then initialize the amount of change to give back depending on how much the customer did overpay if they did */
                {
                    change_amount = coin_count - price;

                } else {
                    change_amount = coin_count; /* If the change_version is set to false then set the change amount to the amount the customer put into the machine */
                }

                if (change_amount == NICKEL || change_amount == DIME)
                {
                    if (change_amount == NICKEL) /* If the change amount is 5 centimes then set the amount of nickels to give back equal to 1 */
                    {
                        nickel_amount = 1;
                    } else {
                        dime_amount = 1; /* If the change amount is 10 centimes then set the amount of dime to give back equal to 1 */
                    }

                }

                if (change_amount > DIME)
                {
                    dime_amount = change_amount / DIME; /* If the change amount is greater than 10 then set the dime amount equal to the change amount divided by 10 and the result will be floored*/
                    if (change_amount % DIME != 0) /* Check to see if the change amount is completely divisble by 10 and if not set the nickel amount to 1 */
                    {
                        nickel_amount = 1;
                    }

                }
                printf("     Change given: %d centimes as %d dime(s) and %d nickel(s).\n", change_amount, dime_amount, nickel_amount);
                give_change = false; /* Set give_change back to false */
                coin_count = 0; /* Reset the amount of coins inputted into the machine to 0 */
            }

            if (shutdown) /* If shutdown is true then set customer service to false and exit the loop */
            {
                customer_service = false;
                printf("Shutting down. Goodbye.\n");
            }


        }

    }


    return 0;

}