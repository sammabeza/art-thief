#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COLLECTION 8
#define MAX_MUSEUMS 4
#define MAX_ARTWORKS 6
#define MAX_LENGTH 100

typedef struct
{
    char name[MAX_LENGTH];
    char description[MAX_LENGTH];
    int security_level;
    int crowd_level;
    int prestige; // affects reputation gain/loss
} Museum;

typedef struct
{
    char title[MAX_LENGTH];
    char artist[MAX_LENGTH];
    char type[MAX_LENGTH];
    char description[MAX_LENGTH];
    int size; // affects difficulty
    int value; // money value
    int notoriety; // how much heat this brings
} Art;

typedef struct
{
    Art collection[MAX_COLLECTION];
    int art_count;
    int reputation; // higher = access to better museums
    int heat; // too much = game over
    int total_value;
} Player;

// Museums with character
Museum museums[] = 
{
    {"The Corner Gallery", "A small, poorly-lit gallery where security naps during lunch", 1, 2, 1},
    {"Riverside Museum", "Mid-tier museum with rotating exhibits and decent foot traffic", 4, 5, 3},
    {"Metropolitan Arts Center", "Prestigious museum with laser grids and armed guards", 7, 6, 6},
    {"The Private Collection", "Invitation-only gallery for the ultra-wealthy", 9, 1, 8}
};

Art artworks[] = 
{
    {"Melancholy #3", "Sarah Chen", "Oil Painting", "A haunting portrait that seems to follow you", 3, 2500, 2},
    {"The Iron Rose", "Viktor Kozlov", "Sculpture", "Twisted metal that somehow captures fragility", 6, 8000, 4},
    {"Digital Dreams", "Anonymous", "Installation", "Holographic butterflies trapped in glass", 4, 12000, 3},
    {"Portrait of Lady Ashworth", "Classical Master", "Renaissance Painting", "Rumored to be cursed", 5, 25000, 7},
    {"The Weeping Stone", "Ancient Artist", "Ancient Artifact", "Pre-Columbian jade mask of unknown origin", 7, 45000, 9},
    {"Suburban Nightmare", "Johnny Risk", "Street Art", "Banksy-style piece on actual brick wall", 8, 15000, 5}
};

// Function prototypes
void clear_input_buffer(void);
int get_int(const char *prompt);
void get_string(const char *prompt, char *str);
void show_status(Player p);
void choose_target(Museum *chosen_museum, Art *chosen_art, Player p);
bool plan_heist(Museum m, Art a, Player *p);
bool execute_heist(Museum m, Art a, int plan_bonus);
void add_to_collection(Player *p, Art a, bool success);
void view_collection(Player p);
bool can_access_museum(Museum m, Player p);

int main(void)
{
    srand(time(NULL));
    Player player = {.art_count = 0, .reputation = 1, .heat = 0, .total_value = 0};
    
    printf("THE ART OF THEFT\n");
    printf("================\n\n");
    printf("You are a discerning art thief with a taste for the extraordinary.\n");
    printf("Build your reputation, but don't let the heat get too high...\n\n");
    
    while (true)
    {
        show_status(player);
        
        // Check if heat is too high
        if (player.heat >= 15)
        {
            printf("\n--- GAME OVER ---\n");
            printf("The authorities have caught up with you. Your crime spree ends here.\n");
            break;
        }
        
        // Check if collection is full
        if (player.art_count >= MAX_COLLECTION)
        {
            printf("\n--- RETIREMENT ---\n");
            printf("Your private gallery is complete. Time to disappear into the shadows.\n");
            break;
        }
        
        Museum target_museum;
        Art target_art;
        choose_target(&target_museum, &target_art, player);
        
        printf("\n--- THE HEIST ---\n");
        printf("Target: \"%s\" by %s\n", target_art.title, target_art.artist);
        printf("Location: %s\n", target_museum.name);
        printf("Description: %s\n", target_art.description);
        
        if (plan_heist(target_museum, target_art, &player))
        {
            printf("\n--- SUCCESS ---\n");
            printf("The piece is yours. %s\n", target_art.description);
            add_to_collection(&player, target_art, true);
        }
        else
        {
            printf("\n--- COMPLICATIONS ---\n");
            printf("Things didn't go as planned...\n");
            add_to_collection(&player, target_art, false);
        }
        
        char choice[MAX_LENGTH];
        get_string("\nContinue your criminal career? (yes/no): ", choice);
        if (strcmp(choice, "yes") != 0 && strcmp(choice, "y") != 0)
        {
            break;
        }
        printf("\n");
    }
    
    printf("\n--- FINAL COLLECTION ---\n");
    view_collection(player);
    printf("\nTotal Portfolio Value: $%d\n", player.total_value);
    printf("Final Reputation: %d\n", player.reputation);
    printf("Heat Level: %d/15\n", player.heat);
    
    return 0;
}

void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int get_int(const char *prompt)
{
    int num;
    while (true)
    {
        printf("%s", prompt);
        if (scanf("%d", &num) == 1)
        {
            clear_input_buffer();
            return num;
        }
        else
        {
            printf("Please enter a valid number.\n");
            clear_input_buffer();
        }
    }
}

void get_string(const char *prompt, char *str)
{
    printf("%s", prompt);
    if (fgets(str, MAX_LENGTH, stdin))
    {
        str[strcspn(str, "\n")] = 0; // Remove newline
    }
}

void show_status(Player p)
{
    printf("--- STATUS ---\n");
    printf("Reputation: %d | Heat: %d/15 | Collection: %d/%d\n", 
           p.reputation, p.heat, p.art_count, MAX_COLLECTION);
    printf("Portfolio Value: $%d\n\n", p.total_value);
}

void choose_target(Museum *chosen_museum, Art *chosen_art, Player p)
{
    printf("Available targets:\n\n");
    
    // Show accessible museums
    for (int i = 0; i < MAX_MUSEUMS; i++)
    {
        if (can_access_museum(museums[i], p))
        {
            printf("%d. %s\n", i + 1, museums[i].name);
            printf("   %s\n", museums[i].description);
            printf("   Security: %d | Crowds: %d | Prestige: %d\n\n", 
                   museums[i].security_level, museums[i].crowd_level, museums[i].prestige);
        }
        else
        {
            printf("%d. [LOCKED] %s (Reputation %d required)\n\n", 
                   i + 1, museums[i].name, museums[i].prestige);
        }
    }
    
    int museum_choice;
    do
    {
        museum_choice = get_int("Choose museum: ") - 1;
    } 
    while (museum_choice < 0 || museum_choice >= MAX_MUSEUMS || 
           !can_access_museum(museums[museum_choice], p));
    
    *chosen_museum = museums[museum_choice];
    
    printf("\nAvailable pieces:\n\n");
    for (int i = 0; i < MAX_ARTWORKS; i++)
    {
        printf("%d. \"%s\" by %s\n", i + 1, artworks[i].title, artworks[i].artist);
        printf("   %s\n", artworks[i].description);
        printf("   Value: $%d | Risk: %d\n\n", artworks[i].value, artworks[i].notoriety);
    }
    
    int art_choice = get_int("Choose artwork: ") - 1;
    *chosen_art = artworks[art_choice % MAX_ARTWORKS];
}

bool can_access_museum(Museum m, Player p)
{
    return p.reputation >= m.prestige;
}

bool plan_heist(Museum m, Art a, Player *p)
{
    printf("\n--- PLANNING PHASE ---\n");
    printf("How do you want to approach this?\n\n");
    printf("1. Quick and dirty - minimal planning, higher risk\n");
    printf("2. Standard approach - balanced risk and reward\n");
    printf("3. Elaborate scheme - lower risk, but more time and resources\n");
    
    int plan = get_int("Choose approach: ");
    int plan_bonus = 0;
    int heat_modifier = 0;
    
    switch (plan)
    {
        case 1:
            printf("\nYou decide to wing it. Sometimes the best plans are no plans...\n");
            plan_bonus = -2;
            heat_modifier = 2;
            break;
        case 2:
            printf("\nYou spend a few days casing the joint. Standard but effective.\n");
            plan_bonus = 0;
            heat_modifier = 1;
            break;
        case 3:
            printf("\nYou meticulously plan every detail. This will take time, but...\n");
            plan_bonus = 3;
            heat_modifier = 0;
            break;
        default:
            plan_bonus = 0;
            heat_modifier = 1;
    }
    
    bool success = execute_heist(m, a, plan_bonus);
    p->heat += a.notoriety + heat_modifier;
    
    return success;
}

bool execute_heist(Museum m, Art a, int plan_bonus)
{
    int total_difficulty = m.security_level + m.crowd_level + a.size;
    int success_threshold = total_difficulty - plan_bonus;
    int roll = rand() % 20 + 1;
    
    printf("\nExecuting the heist...\n");
    printf("Difficulty: %d | Your roll: %d\n", success_threshold, roll);
    
    return roll >= success_threshold;
}

void add_to_collection(Player *p, Art a, bool success)
{
    if (success && p->art_count < MAX_COLLECTION)
    {
        p->collection[p->art_count++] = a;
        p->total_value += a.value;
        p->reputation += (a.notoriety / 3); // reputation grows with bold heists
        printf("Added to collection! Reputation increased.\n");
    }
    else if (!success)
    {
        p->heat += 2; // extra heat for failed attempts
        printf("You escaped empty-handed, but the heat is rising...\n");
    }
}

void view_collection(Player p)
{
    if (p.art_count == 0)
    {
        printf("Your collection is empty.\n");
        return;
    }
    
    for (int i = 0; i < p.art_count; i++)
    {
        printf("%d. \"%s\" by %s ($%d)\n", 
               i + 1, p.collection[i].title, p.collection[i].artist, p.collection[i].value);
        printf("   %s\n\n", p.collection[i].description);
    }
}