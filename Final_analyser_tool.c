#include <stdio.h>
#include <string.h>
// this is an updated codebase
/*
FIXES:1.The hardcoded limit is re-caliberated to take n data entries from file using rewrite(fp);
2.The UNIX seconds_watched is actually corrected to take inputs as watch duration in seconds.
3. FEATURE ADDITION: Search for global show names and pull their watch-history.
4.Refined CLI experience;
*/
struct user_data
{
    char username[100];
    char showname[100];
    char genre[100];
    long seconds_watched; // 1719912605 is a UNIX base seconds_watched showing no. of seconds passed from JAN 1 1970
};
void terminate()
{
    printf("No such File exists,if you think this is an error, contact Administrator.");
}
void show_unwatched()
{
    printf("\n \n This show has a watch count of 0, kindly refer it to recommendations desk.\n");
}

void view_data()
{
    FILE *fp;
    fp = fopen("userdatav1.2.txt", "r");
    if (fp == NULL)
    {
        printf("No such records found.");
        terminate();
    }

    // printing the entire record.
    printf("The user records is as follows: \n \n");
    char lines[1000];
    while (fgets(lines, 1000, fp))
    {
        printf("%s", lines);
    }
    fclose(fp);
}

void user_summary()
{
    // building subtle analytics points
    // scanning the data-sets to anaylyse various points using fscanf

    FILE *fp;
    fp = fopen("userdatav1.2.txt", "r");

    if (fp == NULL)
    {
        printf("No such records found.");
        terminate();
    }

    struct user_data stats;
    int count = 0;
    long long total_watch_hrs_on_platform = 0;
    long long dummy = total_watch_hrs_on_platform;
    while (fscanf(fp, " %[^\n]\n %[^\n]\n %s\n %ld", stats.username, stats.showname, stats.genre, &stats.seconds_watched) == 4)
    {
        printf("\n%s\n", stats.username);
        printf("%s\n", stats.showname);
        printf("%s\n", stats.genre);
        printf("%ld\n", stats.seconds_watched);
        count++;
        dummy = dummy + stats.seconds_watched;
    }

    float watch_hrs = (float)dummy / 3600.00;
    float avg = watch_hrs / count;
    printf("\n\nTotal users recorded: %d", count);
    printf("\nTotal watch hrs on platform: %.2f", watch_hrs);
    printf("\nAverage watch hrs/user_data: %.2f", avg);

    fclose(fp);
}

void analytics()
{

    FILE *fp;
    fp = fopen("userdatav1.2.txt", "r");

    if (fp == NULL)
    {
        printf("No such records found.");
        terminate();
    }

    struct user_data stats;

    int count = 0;

    while (fscanf(fp, " %[^\n]\n%[^\n]\n%s\n%ld", stats.username, stats.showname, stats.genre, &stats.seconds_watched) == 4)
    {
        // scanning file once to find number of entries in file
        count++;
    }
    rewind(fp); // 🔥 piece of code// did this so that for next scanning file-pointer is back to start.

    // now finding the user with highest watch-time

    // trying to use an array to input values of the seconds watched
    long arr[count]; // array with no. of elements as total number of user records
    int i = 0;
    // re-scanning the file so as to arrange watch-seconds in ascending order
    while (fscanf(fp, " %[^\n]\n %[^\n]\n %s\n %ld", stats.username, stats.showname, stats.genre, &stats.seconds_watched) == 4)
    {
        // now entering value into the array

        arr[i] = stats.seconds_watched;
        i++;
    }

    // checking if my array method worked!
    /*printf("\n \n\n\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%ld ,", arr[i]); // yes it works fabulously.✅
    }*/

    // now sorting the seconds_watched array to get the highest and lowest watch times
    long temp;
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            } // ✅✅✅ the technical [patch] works perfect.
        }
    }
    // printing the sorted array

    printf("\n \n The user watchtime in seconds in ascending order: ");
    for (int i = 0; i < count; i++)
    {
        printf("%ld ,", arr[i]); // yes it works fabulously.✅
    }
    printf("\nThe user with highest watch-time is having watch time of(seconds): %ld", arr[count - 1]);

    fclose(fp);
}

void golden_user()
{
    // fxn to print the details of user having highest watch time

    FILE *fp;
    fp = fopen("userdatav1.2.txt", "r"); // especially opened file in read mode to prevent accidental changing of original logs

    if (fp == NULL)
    {
        printf("No such records found.");
        terminate();
    }

    struct user_data golden;

    printf("Enter the highest watchtime received by 'View user watchtime' feature: ");
    long user_watch;
    scanf("%ld", &user_watch);

    while (fscanf(fp, " %[^\n]\n%[^\n]\n%s\n%ld", golden.username, golden.showname, golden.genre, &golden.seconds_watched) == 4)
    {
        if (user_watch == golden.seconds_watched)
        {
            printf("\n%s\n", golden.username);
            printf("%s\n", golden.showname);
            printf("%s", golden.genre);
            printf("%ld", golden.seconds_watched);
        }
    }
    fclose(fp);
}

void show_search()
{
    // fxn to search for particular shows
    FILE *fp;
    fp = fopen("userdatav1.2.txt", "r");

    if (fp == NULL)
    {
        printf("No such records found.");
        terminate();
    }

    struct user_data find_show;

    printf("\nEnter show name to be searched: ");
    char operator_input[100];
    scanf(" %99[^\n]", operator_input);
    printf("\n \n");

    int show_count = 0;
    float total_watch_time = 0;

    printf("Search Results: \n");
    while (fscanf(fp, " %[^\n]\n%[^\n]\n%s\n%ld", find_show.username, find_show.showname, find_show.genre, &find_show.seconds_watched) == 4)
    {
        if (strcmp(operator_input, find_show.showname) == 0)
        {
            printf("\nShow found in Recent Watch Records.\n");
            show_count++;
            total_watch_time += find_show.seconds_watched;
        }
    }
    if (show_count == 0)
    {
        show_unwatched(); // called the helper message-display fxn.
    }
    else
    {
        float avg_show_time = total_watch_time / show_count; // this is in seconds
        float avg_show_time_hrs = avg_show_time / 3600;
        printf("\nNumber of times show watched: %d\n", show_count);
        printf("\nAvg Watch Hrs of this show globally: %.2f\n", avg_show_time_hrs);
    }
    fclose(fp);
}

void watchtime_per_show()
{

    // fxn to store all the movie names in an array, so that watch hrs of all the shows can be determined.
    char *show_names[] = {
        // we use a * because we either do show_names[][200](specify the name max length of each element) or use a pointer.
        "1899",
        "1983",
        "A Nearly Normal Family",
        "Adolescence",
        "Alice in Borderland",
        "Arcane",
        "Baby",
        "Barbarians",
        "Beforeigners",
        "Behind Her Eyes",
        "Biohackers",
        "Black Doves",
        "Black Mirror",
        "Black Spot",
        "Bodies",
        "Bodyguard",
        "Borgen",
        "Bosch",
        "Breaking Bad",
        "Bridgerton",
        "Broadchurch",
        "Chernobyl",
        "Clark",
        "Criminal: France",
        "Criminal: Germany",
        "Criminal: Spain",
        "Criminal: UK",
        "Dark",
        "Deadwind",
        "Dexter",
        "Doctor Who",
        "Dogs of Berlin",
        "Family Business",
        "Foundation",
        "Friends",
        "Gloria",
        "Gomorrah",
        "Happy Valley",
        "House of Cards",
        "House of the Dragon",
        "Into the Night",
        "Katla",
        "Loki",
        "Lost",
        "Lupin",
        "Luther",
        "Maestro in Blue",
        "Manifest",
        "Marseille",
        "Mindhunter",
        "Money Heist",
        "Narcos",
        "Occupied",
        "Ozark",
        "Peaky Blinders",
        "Prison Break",
        "Quicksand",
        "Ragnarok",
        "Reacher",
        "Represent",
        "Ripley",
        "Safe",
        "Severance",
        "Sherlock",
        "Silo",
        "Slow Horses",
        "Stay Close",
        "Stranger Things",
        "Suburra",
        "Succession",
        "Suits",
        "The Bear",
        "The Boys",
        "The Break",
        "The Capture",
        "The Chestnut Man",
        "The Crown",
        "The Diplomat",
        "The English Game",
        "The Fall",
        "The Gentlemen",
        "The Haunting of Hill House",
        "The Last Kingdom",
        "The Last of Us",
        "The Lincoln Lawyer",
        "The Mandalorian",
        "The Night Agent",
        "The Night Manager",
        "The Office",
        "The Penguin",
        "The Punisher",
        "The Queen's Gambit",
        "The Recruit",
        "The Residence",
        "The Sandman",
        "The Spy",
        "The Stranger",
        "The Tourist",
        "The Umbrella Academy",
        "The Valhalla Murders",
        "The Walking Dead",
        "The Witcher",
        "The Wire",
        "The Woods",
        "Trapped",
        "True Detective",
        "Utopia",
        "Vikings",
        "Wednesday",
        "Westworld",
        "You",
        "Young Royals",
        "Young Wallander",
        "The Rain",
        "The Playlist",
    };
    int count = sizeof(show_names) / sizeof(show_names[0]);
    printf("The number of shows in watch list: %d", count); //

    FILE *fp;
    fp = fopen("userdatav1.2.txt", "r");
    struct user_data show_watch_time;

    int i = 0;
    long particular_watch_time = 0.00;

    for (int i = 0; i < count; i++)
    {
        rewind(fp);
        particular_watch_time = 0.00;
        while (fscanf(fp, " %[^\n]\n%[^\n]\n%s\n%ld", show_watch_time.username, show_watch_time.showname, show_watch_time.genre, &show_watch_time.seconds_watched) == 4)
        {
            // resetting it to 0 each iteration.
            if (strcmp(show_names[i], show_watch_time.showname) == 0)
            {
                particular_watch_time += show_watch_time.seconds_watched;
                printf("\nShow name: %s", show_watch_time.showname);
                printf("  Global total Time watched: (in seconds)--> %ld\n\n", particular_watch_time);
            }
        }
    }
}
int main()
{

    // In this project, i build a watch-history analyser for Netflix.
    while (1)
    {
        printf("\n \n");
        printf("Welcome Analyst👋🏻\n");
        printf("See Global Watch Data: 1\n");
        printf("View user summary: 2 \n");
        printf("See analytics: 3\n");
        printf("See Golden user: 4\n");
        printf("Search for a Show: 5\n");
        printf("View Watch time per show: 6 \n \n");
        printf("Exit: 7\n \n");

        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
            view_data();
        }
        else if (choice == 2)
        {
            user_summary();
        }
        else if (choice == 3)
        {
            analytics();
        }
        else if (choice == 4)
        {
            golden_user();
        }
        else if (choice == 5)
        {
            show_search();
        }
        else if (choice == 6)
        {

            watchtime_per_show();
        }
        else if (choice == 7)
        {
            printf("\nThank you Analyst 👋🏻");
        }
        else
        {
            printf("Unidentified Input, restart program.");
        }
    }

    return 0;
} // Final modifications made to project on [12th July,2026],11:51 a.m.[1783837260]
// Project marked as completed ✅ ✅ ✅