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
        printf("Exit: 6 \n \n");

        int choice;
        scanf("%d", &choice);
        if (choice % 1 == 0)
        {
            if (choice == 1)
            {
                view_data();
                /* code */
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
                /* code */

                printf("Thank You Analyst 👋🏻");
                break;
            }
            else
            {
                printf("Unidentified Input, restart program.");
            }
        }
        else
        {
            terminate();
            return 0;
        }
    }

    return 0;
}