/*
 *
 *  Created on: Apr 30, 2018
 *      Author: Gilbert Alvarado
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student_struct
{
    char name[16];
    int age;
    float gpa;
    struct student_struct *next;
} Student;

Student head; //The head of the linked list
//Student *headPTR;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* Given the student values, initialize a structure,
   and return a pointer to the struct */
Student *makeStudent(char name[16], int age, double gpa)
{
    //TODO: Implement this function
	
	Student *newStudent = NULL;//declaration of new student

	newStudent = (Student*)malloc(sizeof(Student));//allocating space in memory
											//for student to be entered in list
											
	strcpy(newStudent->name,name);//assigning data from file to student info
	newStudent->age = age;//assigning age data from file to student data
	newStudent->gpa = gpa;//assigning gpa data from file to student data
	
	newStudent->next = NULL;//new student has been created, student is isolated
							//its pointing to NULL

    return newStudent;//returning newStudent/isolated student
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* Inserts an element to the front of the linkedList */
void push(Student *student)//list head insert
{
    //TODO: Implement this function

	if(student == NULL)//for practice/if you're creating a new list
		head.next = student;//taken care of in main
	else
	{
		student->next = head.next;//have Student at head 
		head.next = student;//linking each student 
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* Traverses the linked list and returns the student with the best GPA */
Student *findTopStudent()
{
    //TODO: Implement this function
	Student *cursor = NULL;//cursor will loop through the list

	Student *topStudent = NULL;//student to be returned
	float bestGPA = 0.0;//gpa to be assigned/compared

	for(cursor = head.next; cursor != NULL; cursor = cursor->next)
	{
		if(cursor->gpa > bestGPA)//if the CURRENT student's gpa is greater than the 
		{						//assigned gpa, the topStudent has been located
		
			bestGPA = cursor->gpa;//assign the current student's gpa to bestGPA
			//it will be used to be compared with the other students gpa within the list
								  
			topStudent = makeStudent(cursor->name, cursor->age, bestGPA);
			//using makeStudent function to assign topStudent with the currentStudent
			
		}//keep looping until the last student/node has been reached
	}
    return topStudent;//returning topStudent
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* Traverses the linked list and returns the average GPA across all students */
float getAverageGPA()
{
    const Student *cursor = NULL;
	/*
	why const? the cursor is not meant to change any of the students data.
	it's only traversing the list.
	*/
    float GPAsum = 0.0;//adds all the gpa's in the list
    int totalGPAs = 0;//keeps track of how many gpa's are in the list

    for(cursor = head.next; cursor != NULL; cursor = cursor->next)
    {
    	GPAsum = GPAsum + cursor->gpa;//adding gpa's
    	++totalGPAs;//increment for every student in list
    }

    return (GPAsum / totalGPAs);//returning mean
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//my added functions
void printList()
{
	Student *cursor = NULL;

	for(cursor = head.next; cursor != NULL; cursor = cursor ->next)
	{
		printf("Name: %s, Age: %d, GPA: %lf\n",cursor->name,cursor->age, cursor->gpa);
	}
}

void freeMemory(Student *list)
{
	Student *cursor = NULL;
	
	while(list != NULL)//free one student at a time
	{
		cursor = list;
		list = list->next;
		printf("%s, %d,with a GPA of %lf has been released.\n",cursor->name, cursor->age, cursor->gpa);
		free(cursor);
	}
}
int main(int argc, char **argv)
{
	
    if(argc != 2){
        perror("ERROR: Wrong number of command line args!\n");
        return -1;
    }
	

    head.next = NULL; //initialize that the linked list is empty.
    FILE * file;
    file = fopen(argv[1] , "r");
    if (!file){
        perror("ERROR opening file!\n");
        return -1;
    }

    //-------------------------------------------------
    // TODO:  Change main method code BELOW

    char s1[16];
    char s2[16];
    char s3[16];
    int age = 0;
    float gpa = 0.0;
    while (fscanf(file, "%s %s %s", s1,s2,s3)!=EOF)
    {

    	//name, age, GPA
        printf("READING FILE LINE: %s %s %s\n",s1, s2, s3);
		
        age = atoi(s2);//converting values to their respective dataType
        gpa = atof(s3);//converting values to their respective dataType
		
        if(head.next == NULL)//already true so this will execute first
        {
        	head.next = makeStudent(s1,age,gpa);//will execute FIRST
        }
        else
        {
        	push(makeStudent(s1,age, gpa));//creating and pushing every student into list
        }
    }
    fclose(file);

    // TODO:  Change main method code ABOVE
   //-------------------------------------------------

    Student *topStudent = findTopStudent();
    printf("\n\nThe Student with the best GPA is: %s\n", topStudent->name);
    printf("The average GPA is: %.2f\n\n\n", getAverageGPA());

    //printList();
	
	freeMemory(head.next);
	
    //while(head.next == NULL)//deallocating memory
    	//free(head.next);//until head.next is pointing to NULL
		
		
	printf("\nYour Top Student, %s age %d with a GPA of %lf, has been released...\n",
	        topStudent->name, topStudent->age, topStudent->gpa);
    free(topStudent);

    return 0;
}
