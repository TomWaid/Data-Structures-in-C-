#include <iostream>
#include <fstream>
#include <string>

// Header for parsing command line arguments.
#include "ArgumentManager.h"

/*

these are the attriutes
{id:1234567,first:Mary,last:Green,DOB:1996-10-03,GPA:4.0}
{id:1234568,first:Peter,last:White,DOB:1997-05-22,GPA:3.8}
{id:1654238,first:Nick,last:Park,DOB:1995-08-18,GPA:4.0}
{id:1234587,first:Katy,last:Green,DOB:1995-08-18,GPA:4.0}




Eric this is how the TA recomended to do this. Below this I pasted my code.
I can figure out the sorting algorithms but getting it into the struct array
is missing me. I cant figure out how to put te linked list into the struct
array like the ta mentions.



This homework does not ask you to sort by GPA, id. it can be sorted
by anything in the attributes.txt. Do not hard coding. See test case 6
in  http://www2.cs.uh.edu/~cotrikxu/ta/cosc2430/2018/spring/test-cases/hw1/.


First, you need to get the attributes you need to compare. for example read
attributes  to an array attributes[]


struct pair {
    string key,
    string value
}

assume you need to compare attributes = {uvw, xyz, abd}.

all attributes in the record are
0 1   2   3   4   5   6   ... 100
a abd xyz ddd uvw xxx lll ...


Then you need to find out the compareId in the record. for the example above, it is {4, 2, 1}.
assume each record has 100 attributes.

struct Record {
     pair attributes[100];
}

Then in sorting, you need to define the less function

bool less (const Record& a, const Record&b) {
       for (int i = 0; i < lengthofcompIds; ++i) {
             if (a.attributes[compIds[i]].value) < b.attributes[compIds[i]].value) return true;
             else if (... >... ) return false;
      }
      return false;
}


Then in the sorting function, use the less function to compare two records.

like   selectsort(Record arr[], int n)  {
        ...
           if (arr[i] < arr[j]) {
               ...
           }
       ...
}

use the following

selectsort(Record arr[], int n) {
        ...
           if (less(arr[i], arr[j])) {
               ...
           }
       ...
}

another way is overload a  < operator in the struct Record.

struct Record {
    pair attributes[100];

    bool operator <  (const Record& other) const{
           for (int i = 0; i < lengthofcompIds; ++i) {
                 if (this->attributes[compIds[i]].value) < other.attributes[compIds[i]].value) return true;
                 else if (... >... ) return false;
          }
          return false;
    }
}

then you can reuse the any sorting function from the book or from the internet with changing only from the type int to Record.

void sort(int a[], int n);   // book or internet

void sort(Record a[], int n);

Here is my code

*/

using namespace std;

/// NOT ALLOWED TO USE
/// stl library like vector, list, queue, stack, map, set,
/// unordered map, unordered set and std::sort

/// Assignment Restrictions
/// Timeout: 10 seconds
/// Maximum number of attributes: 100
/// Maximum number of records: 100,000

/// We don't know how many attributes there might be, but TA said 100 is the max.

/// Each record looks like this:
/// a:1   b:9999   c:1   d:100000   e:1   f:100000   g:7
/// The attribute key is on left side of colon : and the attribute value is on the right.

// old code
/*
struct pair{
    string key;
    string value;
};
struct Record {
    string key;
    string* Array;
    string value;
    friend ostream& operator<<(ostream& os, const Record& dt);
}attributes[100];
struct element {

    string info;

    string idNumber;
    string firstName;
    string DOB;
    string GPA;
    string lastName;
    string endBracket;
    friend bool operator< (const element &c1, const element &c2);


};
*/

struct Pair
{
    string key;
    string value;
};

/// Each record will keep an array of Pair to hold the attribute data.
struct Record
{
    /// There can be any number of attributes. Find out how many there are later.
    Pair* data = nullptr;
    friend ostream & operator<< (ostream& os, const Record& record);
};

/// Store attribute names into an array.
/// Count number of attributes per record and store into variable.
string* attribute_names = nullptr;
int attribute_count = 0;

/// An array to hold the indexes of the attribute names that need to be compared.
/// Also keep track of its size.
int* compare_indexes = nullptr;
int compare_count = 0;

// old code
/*
ostream& operator<<(ostream& os, const Record& dt)
{


    os << dt.value<< endl;
    return os;
}
*/

ostream & operator<< (ostream& os, const Record& record)
{
    /// Print the opening bracket {
    os << "{";

    /// Loop through the data of the record and print each key and value except for last one.
    for (int i = 0; i < attribute_count - 1; ++i)
    {
        /// separate key and value with a colon :
        /// separate each pair with a comma ,
        os << record.data[i].key << ":" << record.data[i].value << ",";
    }

    /// Print the last key and value
    os << record.data[attribute_count - 1].key << ":" << record.data[attribute_count - 1].value;

    /// Print the closing bracket }
    os << "}";

    return os;
}

// old code
/*
struct node

{

    string info;

    string idNumber;
    string firstName;
    string DOB;
    string GPA;
    string lastName;
    string endBracket;

    struct node *next;

    struct node *prev;

};
*/

/// Each node in the doubly linked list will hold a single record.
struct Node
{
    Record record;
    struct Node* next {};
    struct Node* prev {};
};

class double_llist
{
public:

    /// no longer needed
    //void create_list (char var);

    // old: void add_begin(string var);
    void add_begin (const string& record);

    // have not been implemented yet
    //void add_after (int value, int position);
    //void delete_element (int value);
    //void search_element (int value);

    void display_dlist () const;

    int count () const;

    void reverse ();

    /// don't need this
    //double_llist ()
    //{
    //    start = nullptr;
    //}

    // old: node *start;
    struct Node* start = nullptr;
};

/// This no good
//bool operator< (const element& c1, const element& c2)
//{
//    return (c1.idNumber < c2.idNumber || c1.firstName < c2.firstName || c1.lastName < c2.lastName || c1.GPA < c2.GPA || c1.DOB < c2.DOB);
//}

/// Don't need this anymore
//void double_llist::create_list (char value)
//
//{
//    struct node * s {}, * temp {};
//
//    /* temp = new(struct node);
//
//    temp->info = value;
//
//    temp->next = NULL;
//
//    if (start == NULL)
//
//    {
//
//        temp->prev = NULL;
//
//        start = temp;
//
//    }
//
//    else
//
//    {
//
//
//        while (s->next != NULL)
//
//            s = s->next;
//
//        s->next = temp;
//
//        temp->prev = s;
//
//    }
//        s = start;
//
//cout<< "Node created" << endl;
//*/
//}

// old code
/*
void double_llist::add_begin(string value) {
    string partial;
    int count =0;
    string row;
    string row2;

    struct node *temp;
    temp = new(struct node);

    if (start == NULL) {
        start = temp;
        start->prev = NULL;
    }else{
        temp->prev = NULL;
        temp->next = start;
        start->prev = temp;
        start = temp;
    }

    // find partial
    std::size_t pos = value.find('}');
    if (pos != std::string::npos) {
        partial = value.substr(0, pos+1);
        temp->info = partial;

    }


}
*/

void double_llist::add_begin (const string& record)
{
    /// Create a new node to put into doubly linked list.
    struct Node* new_node = new struct Node;

    /// Create dynamic array for record data.
    new_node->record.data = new Pair[attribute_count];

    /// Skip the { at the beginning.
    std::size_t pos1 = record.find('{') + 1; // + 1 to start at next character
    std::size_t pos2 = 0;
    for (int i = 0; i < attribute_count; ++i)
    {
        /// Find attribute key and store into records data.
        pos2 = record.find(':', pos1);
        if (pos2 != std::string::npos)
        {
            new_node->record.data[i].key = record.substr(pos1, pos2 - pos1);
        }
        pos1 = pos2 + 1;
        /// Find attribute value and store into records data.
        pos2 = record.find_first_of(",}", pos1); // find_first_of can search for one of multiple characters
        if (pos2 != std::string::npos)
        {
            new_node->record.data[i].value = record.substr(pos1, pos2 - pos1);
        }
        pos1 = pos2 + 1;
    }

    /// Point new node's prev value to null and next value to start.
    new_node->prev = nullptr;
    new_node->next = start;

    /// If start is not null, point prev value to new node.
    if (start != nullptr)
    {
        start->prev = new_node;
    }

    /// Set start to new node to continue chain.
    start = new_node;
}

// old code
/*
void double_llist::display_dlist()

{

    struct node *q;

    if (start == NULL)

    {

        cout<<"List empty,nothing to display"<<endl;

        return;

    }

    q = start;


    cout<<"The Doubly Link List is :"<<endl;

    while (q != NULL)

    {

        cout<<q->info<<"    ";
        cout<< "This is hw 1"<< "   ";

        q = q->next;

    }


    cout<<endl;


}
*/

void double_llist::display_dlist () const
{
    if (start == nullptr)
    {
        cout << "List empty, nothing to display." << endl;
        return;
    }

    struct Node* q = start;

    /// TODO: Remove this before turning assignment in.
    /// Testing code.
    cout << "The Doubly Link List is :" << endl;
    int count = 0;
    /// End testing code.

    while (q != nullptr)
    {
        cout << q->record << endl;
        q = q->next;

        /// TODO: Remove this before turning assignment in.
        /// Testing code.
        count++;
        if (count == 10)
            break;
        /// End testing code.
    }
}

// old code
/*
int double_llist::count()

{

    struct node *q = start;

    int cnt = 0;

    while (q != NULL)

    {

        q = q->next;

        cnt++;

    }

    cout<<"Number of elements are: "<<cnt<<endl;
    return cnt;
}
*/

int double_llist::count () const
{
    struct Node* q = start;

    int count = 0;

    while (q != nullptr)
    {
        q = q->next;
        count++;
    }

    /// TODO: Remove this before turning assignment in.
    cout << "Number of elements are: " << count << endl;

    return count;
}

// old code
/*
void double_llist::reverse()

{

    struct node *p1, *p2;

    p1 = start;

    p2 = p1->next;

    p1->next = NULL;

    p1->prev = p2;

    while (p2 != NULL)

    {

        p2->prev = p2->next;

        p2->next = p1;

        p1 = p2;

        p2 = p2->prev;

    }

    start = p1;

    cout<<"List Reversed"<<endl;

}
*/

void double_llist::reverse ()
{
    struct Node* p1 = start;
    struct Node* p2 = p1->next;

    p1->next = nullptr;
    p1->prev = p2;

    while (p2 != nullptr)
    {
        p2->prev = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p2->prev;
    }
    start = p1;

    /// TODO: Remove this before turning assignment in.
    cout << "List Reversed" << endl;
}

/// Function to compare two Records
bool operator< (const Record& a, const Record& b)
{
    for (int i = 0; i < compare_count; ++i)
    {
        if (a.data[compare_indexes[i]].value == b.data[compare_indexes[i]].value)
            continue;
        return a.data[compare_indexes[i]].value < b.data[compare_indexes[i]].value;
    }
    return false;
}

void get_attribute_names (const string& record)
{
    /// Count the number of attributes.
    for (char c : record)
    {
        if (c == ':') attribute_count++;
    }

    /// Create dynamic array for attribute names.
    attribute_names = new string[attribute_count];

    /// Skip the { at the beginning.
    std::size_t pos1 = record.find('{') + 1; // + 1 to start at next character
    std::size_t pos2 = 0;
    for (int i = 0; i < attribute_count; ++i)
    {
        /// Find attribute key and store into array.
        pos2 = record.find(':', pos1);
        if (pos2 != std::string::npos)
        {
            attribute_names[i] = record.substr(pos1, pos2 - pos1);
        }
        /// Skip attribute value
        pos1 = record.find(',', pos2 + 1) + 1; // + 1 to start at next character
    }
}

void get_compare_indexes (const string& first_line)
{
    /// Count number of compare names.
    for (char c : first_line)
    {
        if (c == ' ') compare_count++;
    }
    /// Add 1 for the last name.
    compare_count++;

    /// Create dynamic array for compare indexes.
    compare_indexes = new int[compare_count];

    /// Find the index for each name in first_line and store in compare_indexes.
    std::size_t pos1 = 0;
    std::size_t pos2 = 0;
    string compare_name = "";
    for (int i = 0; i < compare_count; ++i)
    {
        /// Find name.
        pos2 = first_line.find(' ', pos1);
        compare_name = first_line.substr(pos1, pos2 - pos1);
        pos1 = pos2 + 1;

        /// Search attribute_names array for the compare_name and store the index.
        for (int j = 0; j < attribute_count; ++j)
        {
            if (attribute_names[j] == compare_name)
            {
                compare_indexes[i] = j;
            }
        }
    }
}

int Partition(Record array[], int i, int k)
{
int l =0;
int h=0;
int midpoint=0;
bool done =false;

midpoint= i+(k-i)/2;
Record pivot =array[midpoint];
l =i;
h=k;
while(!done)
{
while(array[l] < pivot)
{
++l;
}
while(pivot <array[h]){
--h;
}
if(l>=h){
done =true;
}
else
{
Record temp= array[l];
array[l] =array[h];
array[h] =temp;
++l;
--h;
}
}
return h;
}

void Quicksort(Record array[], int i, int k)
{
int j=0;
if(i>=k)
{
return;
}
j =Partition(array,i,k);

Quicksort(array, i,j);
Quicksort(array, j+1,k);
return;
}

void Merge(Record array[], int i, int j, int k)
{
int mergedSize = k-i +1;
int mergePos =0;
int leftPos =0;
int rightPos =0;
Record* mergedRecord =new Record[mergedSize];
leftPos =i;
rightPos = j+1;
while(leftPos <= j && rightPos <= k)
{
if(array[leftPos] < array[rightPos])
{
mergedRecord[mergePos] = array[leftPos];
++leftPos;
}
else
{
mergedRecord[mergePos] =array[rightPos];
++ rightPos;
}
++mergePos;
}
while(leftPos<=j){
mergedRecord[mergePos] = array[leftPos];
++leftPos;
++mergePos;
}
while(rightPos<=k){
mergedRecord[mergePos] =array[rightPos];
++rightPos;
++mergePos;
}
for(mergePos =0; mergePos<mergedSize; ++mergePos)
{
array[i+mergePos] = mergedRecord[mergePos];
}
}
void MergeSort(Record array[], int i, int k){
int j=0;
if(i<k)
{
j =(i+k)/2;
MergeSort(array,i,j);
MergeSort(array,j+1,k);
Merge(array,i,j,k);
}
}
void buildHeap(Record array[], int size, int i)
{
int max =i;
int left =2*i+1;
int right =2*i+2;
if(left<size && array[max] <array[left])
max =left;
if(right <size && array[max]< array[right])
max =right;
if(max!=i)
{
swap(array[i],array[max]);
buildHeap(array,size,max);
}
}

void heapSort(Record array[], int size)
{
for(int i =size/2-1; i>=0;i--)
buildHeap(array,size,i);
for(int i=size-1;i>=0;i--)
{
swap(array[0],array[i]);
buildHeap(array,i,0);
}
}
int main (int argc, char** argv)
{
    /// Need to read program arguments from command line to get file names.
    /// Using the ArgumentManager code given to us under "Resource" at
    /// http://www2.cs.uh.edu/~cotrikxu/ta/cosc2430/2018/spring/

    ArgumentManager argMgr(argc, argv);

    /// The program will be run with this command:
    ///
    /// ./sort input=in1.txt attributes=att1.txt output=out1.txt sort=quick

    string input_fn = argMgr.get("input");
    string attributes_fn = argMgr.get("attributes");
    string output_fn = argMgr.get("output");
    string sort_fn = argMgr.get("sort");

    /// TODO: Remove this before turning assignment in.
    /// Check if working so far.
    //cout << "file: " << input_fn << endl;
    //cout << "file: " << attributes_fn << endl;
    //cout << "file: " << output_fn << endl;
    //cout<< "file: " << sort_fn<< endl;
   
    /// End check.

    // old code
    /*
    double_llist dl;
    ifstream inFS;   // Input file stream
    string fileNum; // File data
    */

    ifstream input_file; // file stream for input
    ofstream output_file; // file stream for output

    // old code
    /*
    // Open input file
    cout << "Opening file myfile.txt." << endl;
    inFS.open("file for reading.txt");
    */

    /// Use input filename taken from command line arguments.

    /// TODO: Remove this before turning assignment in.
    cout << "Opening file " << input_fn << "." << endl;

    input_file.open(input_fn);

    /// Check if file could be opened.
    if (!input_file.is_open())
    {
        cout << "Could not open file " << input_fn << "." << endl;
        return 1;
    }

    // old code
    /*
    // Print read numbers to output
    cout << "Reading and printing numbers." << endl;
    dl.create_list(' ');
    while (!inFS.eof()) {
        inFS >> fileNum;
        if (inFS.good()) {
            dl.add_begin(fileNum);
        }
    }
    inFS.close();
    */

    /// Count number of attributes.
    /// Get attribute names.
    string first_record;
    input_file >> first_record;
    get_attribute_names(first_record);

    /// TODO: Remove this before turning assignment in.
    /// Check if working so far.
    cout << "Number of attributes: " << attribute_count << endl;
    cout << "Attribute names: ";
    for (int i = 0; i < attribute_count; ++i)
    {
        cout << attribute_names[i] << " ";
    }
    cout << endl;
    /// End check.

    /// Start reading from beginning of file again.
    input_file.seekg(input_file.beg);

    /// Read records from file and add to doubly linked list.
    double_llist dl;
    string record;
    while (!input_file.eof())
    {
        input_file >> record;
        /// This check is wrong for reading from a file.
        /// The eof state is set when the end of file is *reached*,
        ///     not when trying to read from the end of file.
        //if (input_file.good())
        //{
        dl.add_begin(record);
        //}
    }
    input_file.close();

    /// TODO: remove before submitting
    /// Check if working so far.
    dl.display_dlist();
    /// End check.

    // old code
    /*
    ifstream inFS2;   // Input file stream
    string fileNum2; // File data

    // Open file
    cout << "Opening file myfile.txt." << endl;
    inFS2.open("atributes.txt");

    if (!inFS2.is_open()) {
        cout << "Could not open file myfile.txt." << endl;
        return 1;
    }

    // Print read numbers to output
    cout << "Reading and printing numbers." << endl;

    while (!inFS2.eof()) {


        for (int i = 0; i < 100; ++i) {
            inFS2 >> attributes[i].key;
        }
    }
    inFS.close();

    for (int i = 0; i < 100; ++i) {
        cout << attributes[i].key;
    }
    */

    ifstream attributes_file; // file stream for attributes

    /// Use attributes filename taken from command line arguments.

    /// TODO: Remove this before turning assignment in.
    cout << "Opening file " << attributes_fn << "." << endl;

    attributes_file.open(attributes_fn);

    /// Check if file could be opened.
    if (!attributes_file.is_open())
    {
        cout << "Could not open file " << attributes_fn << "." << endl;
        return 1;
    }

    /// Read first line from attributes file
    string first_line;
    getline(attributes_file, first_line);

    /// Get compare indexes.
    get_compare_indexes(first_line);
    attributes_file.close();

    /// TODO: Remove this before turning assignment in.
    /// Check if working so far.
    for (int i = 0; i < compare_count; ++i)
    {
        cout << compare_indexes[i] << ":" << attribute_names[compare_indexes[i]] << " ";
    }
    cout << endl;
    /// End check.

    // old code
    /*
    dl.reverse();
    dl.display_dlist();
    cout<< endl<<endl<<endl;
    dl.count();
    cout << "Closing file myfile.txt." << endl;
    struct node *q, *q2;
    q = dl.start;

    int length= dl.count();
    */

    /// Reverse doubly linked list, since records are stored backwards
    dl.reverse();

    /// TODO: remove before submitting
    /// Check if working so far.
    dl.display_dlist();
    /// End check.

    // old code
    /*
    cout << "attributes array";

    string temp;
    cout << "Sorted array";
    q2 = dl.start;

    for (int i = 0; i < length; i++)
    {
        attributes[i].value = q2->info;
        q2 = q2->next;
    }

    for (int i = 0; i < length; i++)
    {
        cout << attributes[i].value << endl;
    }
    */

    /// Need to store records into array.

    /// Need to sort records.

    /// Need to output records to output file.
    struct Node* q1=dl.start;
    int length = dl.count();
    Record *array=new Record[length];
    for(int i=0; i< length;i++){
        array[i] =q1->record;
        q1 =q1->next;
    }
if( sort_fn=="selection"){
cout << "This is the file with the selection sort" << endl;
for( int i =0; i< length; ++i){
 int indexSmallest =i;
for(int j =i+1; j< length; ++j){
if(array[j]<array[indexSmallest]){
indexSmallest =j;
}

}
Record temp= array[i];
array[i]=array[indexSmallest];
array[indexSmallest] =temp;
}
for (int i =0; i< length; i++){
cout<< array[i]<<endl;
}
else if(sort_fn=="insertion"){
cout<< "this is the file with the insertion sort" << endl;

for(int i = 1; i< length; ++i){
int j =i;
while(j >0 && array[j]< array[j-1]){
Record temp =array[j];
array[j] =array[j-1];
array[j -1] =temp;
--j;
}
}
for(int i=0; i< length; i++)
{
cout<<array[i]<<endl;
}
else if( sort_fn=="quick"){
cout<< "This is the file with the quick sort" << endl;
   Quicksort(array,0, length -1);
}

else if(sort_fn=="merge"){
cout << "This is the file with the merge sort" << endl;
MergeSort(array,0,length-1);
for(int i =0; i<length; i++){
cout<<array[i] <<endl;
}
else if(sort_fn=="heap"){
cout << "this is the file with the heap sort" << endl;
heapSort(array,4);
for(int i =0; i< length; i++)
{
cout<< array[i] <<endl;
}
else{
cout<< "a proper title was not chosen for the sort function call"<<endl;
}


for(int i =0; i< length; i++){
cout<< array[i]<<endl;
}


/*    
ofstream outFS;
outFS.open(output_fn);
if (!outFS.is_open()) {
	cout << "Could not open file" << endl;
	return 1;
}
for (int k = 0; k<length; k++)
{
	outFS  <<array[k] << endl; //Outputs array to txtFile
}
outFS.close();
 */


return 0;
}

    //return 0;





 

