#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
typedef struct TimeNode *time;
struct TimeNode;

This structure is defined to record the open / close time of the server.
What deserves your attention is that 
the information of the hour, minute & the second are stored in integer form.
*/
typedef struct TimeNode time;
struct TimeNode
{
	int hour, minute, second;
};

/*
typedef struct TimeLine *timeline;
struct TimeLine;

This structure is used to store the start and end time of a server. 
Define the pointer TimeLine* as timeline to point to the next data of 
the start and end time of a server. 
In this part, the name of the server is not that important, 
because what we only care about is the length of each computing task 
and whether overlapping part exists between two different records. 
So, the name of the server is unnecessary to record.

The start time is hour1, minute1, second1, 
while the second time is hour2, minute2, second2.
*/ 
typedef struct TimeLine *timeline;
struct TimeLine
{
	int hour1, minute1, second1, hour2, minute2, second2;
	timeline next;	
};

/*
typedef struct ServerData *Server;  
struct ServerData;

This structure is designed to store the information of each server, 
containing the name of the server, server_number[7], the time_point, 
which has been discussed earlier, and the integer count_time, 
which is to count the number of the time_point. 
For example, 
if we input "za3q625 11:42:01; za3q625 06:30:50; za3q625 23:55:00", 
the value of the count_time of the point "za3q625" is 3.
*/
typedef struct ServerData Server;  
struct ServerData
{
	/*
	The number of the server;
	*/
	char server_number[7]; 
	
	time time_point[20000]; 
	int count_time;	
};

/*
typedef struct top *list;
struct top;

This structure is used to store all the information of the input.
And that's why it is called "top".
The array in Server type is used to store the information of the servers one by one.
The integer count_server represents the number of the server.
*/
typedef struct top *list;
struct top
{
	Server server_info[10000];
	int count_server;	
};

/*
The structure compute_list is used to store the task 
after all the information is stored in the structure list.
*/
typedef struct compute_list task;
struct compute_list
{
	timeline compute_task;
	int count_task;
};

/*
Initialize the list, 
the number of the server is initialized as 0.
*/
list init_list(void);

/*
Read N queries of the server infomation with format like "xxxxxxx hh:mm:ss", 
then store them by insertion sort or quick sort.
*/
list Read(int n);

/*
The function AddTheData is designed to add the time point to the type task.
The main algorithm is to use a double-while-loop 
in order to read all the time point.
*/
task AddTheData(list general_list);

/*
The function is able to decide 
whether the two input strings are the same 
and return 1 if they are they are the same, return 0 if not. 
Meanwhile, the function can add the time point after the existed record 
if the strings are the same, 
and because the same strings represent the same server,
the data of the same server should be stored together.
*/
int string_compare(list a, char b[], int hour, int minute, int second);

/*
This function has the capability 
to sort the time point in increasing order by insertion sort,
or quick sort.
*/
void add(list a, int hour, int minute, int second, int n);

/*
Compute the total seconds of a time line 
and return the total value in integer type.
*/
int compute_second(int hour1, int minute1, int second1, int hour2, int minute2, int second2);

/*
The function compares the value of two time, 
h1:m1:s1 & h2:m2:s2, 
if h1:m1:s1 > h2:m2:s2, return 1; 
else, return 0.
*/
int compare_time(int hour1, int minute1, int second1, int hour2, int minute2, int second2);

/*
The function insert the time point to the list. 
If the list is empty, add the time point to the server_info[0]
*/
void insert(list a, char name[], int hour, int minute, int second);
int add_time(timeline a, time t1, time t2, int count);

int main ()
{
	/*
	Each input file contains one test case. 
	Each case starts with two positive integers N (¡Ü2¡Á10^4),
    the number of server records, and K (¡Ü8¡Á10^4), 
	the number of queries.  
	*/
	int n, k, i, j;
	scanf("%d %d", &n, &k);
	
	/*
	Task 1:
	Read the input 
	and return the general_list.
	*/
	list general_list = Read(n);
	
	/*
	Task 2:
	Combine the time line 
	and store them in the array 
	in task type.
	*/
	task time_line = AddTheData(general_list);
	
	/*
	Initialize the integer array time_list,
	which is used to store the time lines.
	*/
	int time_list[time_line.count_task];
	
	/*
	Pointer tmp is used to traverse the linked list time_line.compute_task.
	*/
	timeline tmp = time_line.compute_task;
	
	/*
	The integer represents 
	the length of the integer array time_list.
	*/
	int index = 0;
	while (tmp)
	{
		time_list[index++] = compute_second(tmp->hour1, tmp->minute1, tmp->second1, tmp->hour2, tmp->minute2, tmp->second2);
		tmp = tmp->next;
	}
	
	/*
	Find the maximum computation task you could run
	in the integer array time_list.
	*/
	int max = time_list[0];
	for (i = 1; i < index; i++)
		max = (time_list[i] > max) ? time_list[i] : max;
	
	/*
	The integer array answer[k] is used to store 
	the answer, in other word, the total number 
	of valid time points 
	for starting the given computation task.
	*/
	int answer[k];
	for (i = 0; i < k; i++)
	{
		int hour, minute, second;
		scanf("%d:%d:%d", &hour, &minute, &second);
		int t = compute_second(0, 0, 0, hour, minute, second);
		int count_total_time = 0;
		for (j = 0; j < index; j++)
		{
			if (time_list[j] >= t)
			{
				count_total_time += time_list[j] - t + 1;	
			}	
		}
		answer[i] = count_total_time;
	}
	/*
	Output the longest computation task you could run. 
	*/
	printf("\n%d\n", max);
	for (i = 0; i < k; i++)
	{
		/*
		Output the total number 
	    of valid time points 
	    for starting the given computation task, one by one.
		*/
		printf("%d\n", answer[i]);
	} 
	printf("\n");	
	
	/*
	Give the system a pause.
	*/
	system("pause");
	return 0;
}

list init_list(void)
{
	/*
	Init a new list a with function malloc.
	*/
	list a = (list)malloc(sizeof(struct top));
	a->count_server = 0;
	return a;
}

int add_time(timeline a, time t1, time t2, int count)
{
	int i;
	int hour1, minute1, second1, hour2, minute2, second2;
	hour1 = t1.hour, minute1 = t1.minute, second1 = t1.second;
	hour2 = t2.hour, minute2 = t2.minute, second2 = t2.second;
	
	/*
	If count = 0, which means the timeline is NULL, 
	so the input time point is the first one, 
	we need to add it to the head of the timeline 1.
	*/
	if (!count)
	{
		a->hour1 = hour1;
		a->minute1 = minute1;
		a->second1 = second1;
		a->hour2 = hour2;
		a->minute2 = minute2;
		a->second2 = second2;
		count++;
		a->next = NULL;
	}
	/*
	When the timeline a is not empty.
	*/
	else
	{
		timeline obj = (timeline)malloc(sizeof (struct TimeLine));
		timeline tmp = a, s = a;
		obj->hour1 = hour1, obj->minute1 = minute1, obj->second1 = second1;
		obj->hour2 = hour2, obj->minute2 = minute2, obj->second2 = second2;
		obj->next = NULL;
		while (s->next) s = s->next;
		
		s->next = obj;
		count++;
		 
		while (tmp->next)
		{
			if (!compare_time(tmp->hour1, tmp->minute1, tmp->second1, hour1, minute1, second1) && compare_time(tmp->hour2, tmp->minute2, tmp->second2, hour2, minute2, second2))
			{   
			    /*
			    If the new timeline
			    is the subset of the new timeline, 
			    just ignore the new one.
			    */
				obj = NULL;
				count--;
				break;
			}
			else if (compare_time(tmp->hour1, tmp->minute1, tmp->second1, hour2, minute2, second2) || !compare_time(tmp->hour2, tmp->minute2, tmp->second2, hour1, minute1, second1))
			{   
			    /*
				If the two timelines have no overlapping parts, 
				we just need to let the pointer tmp
				points to tmp->next,
				and then continue the while loop.
				*/
				tmp = tmp->next; 
				continue;	
			}
			else 
			{   /*
			    If there is overlapping part between the two time points, 
			    the further discussion is needed.
			    */ 
				
				/*
				If the old time line
				is the subset of the new subset, 
				what we only need to do 
				is to delete the old time line 
				later.
				*/
				if (compare_time(tmp->hour1, tmp->minute1, tmp->second1, hour1, minute1, second1) && !compare_time(tmp->hour2, tmp->minute2, tmp->second2, hour2, minute2, second2));  
				
				/*
				If there is overlapping part, 
				the value of hour1, minute1, second1
				or hour2, minue2, second2,
				will change.
				*/
				else if (!compare_time(tmp->hour1, tmp->minute1, tmp->second1, hour2, minute2, second2) && compare_time(tmp->hour2, tmp->minute2, tmp->second2, hour2, minute2, second2))
				{
					obj->hour2 = tmp->hour2;
					obj->minute2 = tmp->minute2;
					obj->second2 = tmp->second2;
				}
				else if (!compare_time(tmp->hour1, tmp->minute1, tmp->second1, hour1, minute1, second1) && compare_time(tmp->hour2, tmp->minute2, tmp->second2, hour1, minute1, second1))
				{
					obj->hour1 = tmp->hour1;
					obj->minute1 = tmp->minute1;
					obj->second1 = tmp->second1;
				}
				else
				{
					tmp = tmp->next;
					continue;
				}
				if (tmp == a)
					a = a->next;
				else
				{
					timeline load = (timeline)malloc(sizeof (struct TimeLine));
					load = a;
					while(1)
					{
						if (load->next == tmp) break;
						load = load->next;
					}
					load->next = load->next->next;
				}
				count--;
				tmp = tmp->next;
			}
		}
	}
	return count;
}

list Read(int n)
{
	list general_list = init_list();
	int i;
	for (i = 0; i < n; i++)
	{
		char name[7];
		int hour, minute, second;
		scanf("%s %d:%d:%d", name, &hour, &minute, &second);
		/*
		If the server is the first time to read,
		then we need to constructe a new space
		to store the information of the server.
		*/
		if (!string_compare(general_list, name, hour, minute, second))
			insert(general_list, name, hour, minute, second);
	}
	return general_list;
}

task AddTheData(list general_list)
{
	int i, j;
	task time_line;
	time_line.compute_task = (timeline)malloc(sizeof (struct TimeLine));
	time_line.count_task = 0;
	
	/*
	In the double-while loop, 
	traverse the the general list,
	store the total time line in time_line.count_task.
	*/
	for (i = 0; i < general_list->count_server; i++)
	{
		for (j = 0; (j+1) < general_list->server_info[i].count_time; j += 2)
		{
			time_line.count_task = add_time(time_line.compute_task, general_list->server_info[i].time_point[j], general_list->server_info[i].time_point[j+1], time_line.count_task);
		}
	}
	return time_line;
}

int string_compare(list a, char b[], int hour, int minute, int second)
{
	if (!a->count_server) return 0;
	int i, flag = 0;
	for (i = 0; i < a->count_server; i++)
	{
		if (!strcmp(b, a->server_info[i].server_number))
		{
			flag = 1;
			/*
			Add the open / close time of the server which has already exists
			*/
			add(a, hour, minute ,second, i); 
			break;
		}
	}
	if (flag) return 1;
	return 0; 
}

void add(list a, int hour, int minute, int second, int n)
{
	int i;
	if (a->server_info[n].count_time != 0)
	{
		for (i = a->server_info[n].count_time-1; i >= 0; i--)
		{
			if (compare_time(a->server_info[n].time_point[i].hour, a->server_info[n].time_point[i].minute, a->server_info[n].time_point[i].second, hour, minute, second))
			{
				a->server_info[n].time_point[i+1] = a->server_info[n].time_point[i];
			}
			else break;
		}
	}
	a->server_info[n].time_point[i+1].hour = hour;
	a->server_info[n].time_point[i+1].minute = minute;
	a->server_info[n].time_point[i+1].second = second;
	a->server_info[n].count_time++;
}

/*
Compute the total seconds of a time line and return the total value in integer type.
*/
int compute_second(int hour1, int minute1, int second1, int hour2, int minute2, int second2)
{
	/*
	The total length of the time line in second
	is hour*3600+minute*60+second.
	*/
	return (hour2*3600+minute2*60+second2)-(hour1*3600+minute1*60+second1);	
}

/*
The function compares the value of two time, 
h1:m1:s1 & h2:m2:s2.
If h1:m1:s1 > h2:m2:s2, return 1; 
else, return 0.
*/
int compare_time(int hour1, int minute1, int second1, int hour2, int minute2, int second2)
{
	/*
	If timeline1 > timeline2, return 1;
	else return 0.
	*/
	if (hour1 > hour2)
		return 1;
	else if (hour1 < hour2)
		return 0;
	else if (hour1 == hour2)
	{
		if (minute1 > minute2)
			return 1;
		else if (minute1 < minute2)
			return 0;
		else if (minute1 == minute2)
		{
			if (second1 > second2)
				return 1;
			else return 0;
		}
	}	
}

void insert(list a, char name[], int hour, int minute, int second)
{
	/*
	The function insert the time point to the list. 
	If the list is empty, add the time point to the server_info[0]:
	*/
	int i;
	if (!a->count_server) 
	{
		a->server_info[0].count_time = 0;
		a->count_server = 0;
		for (i = 0; i < 7; i++)
			a->server_info[0].server_number[i] = name[i];
		a->server_info[0].time_point[0].hour = hour;
		a->server_info[0].time_point[0].minute = minute;
		a->server_info[0].time_point[0].second = second;
		a->server_info[0].count_time++;
	}
	else 
	{
		a->server_info[a->count_server].count_time = 0;
		for (i = 0; i < 7; i++)
			a->server_info[a->count_server].server_number[i] = name[i];
		a->server_info[a->count_server].time_point[0].hour = hour;
		a->server_info[a->count_server].time_point[0].minute = minute;
		a->server_info[a->count_server].time_point[0].second = second;
		a->server_info[a->count_server].count_time++;
	}
	a->count_server++;
}
