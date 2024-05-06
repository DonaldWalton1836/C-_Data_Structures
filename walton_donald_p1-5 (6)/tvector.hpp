#ifndef _TVECTOR_HPP
#define _TVECTOR_HPP

using namespace std;
//Do I need to implement the friend function here????
template<typename T>  //This is the implementation of the default constructor.
TVector<T>::TVector()
{

    size = 0;
    capacity = 0;
    array = new T[capacity + SPARECAPACITY];

};


template <typename T> //This is the implementation of the parameterized constructor of TVector.
TVector<T>::TVector(T val, int num) //want to create a constructor that creates a vector with a certain number data element copies.
{
    
    capacity = num + SPARECAPACITY;
    size = num;
    array= new T[capacity];
    for(int i = 0; i < num; i++)
    {
        array[i] = val;
    }
};

template <typename T> //This is the destructor.
TVector<T>::~TVector()
{
    delete [] array; //this will delete the vector once it is out of scope.
};

template <typename T> //This is the implementation for the copy constructor.
TVector<T>::TVector(const TVector<T> & v)
{
    
    capacity = v.capacity; //This will copy the capacity.
    size = v.size;//This will copy the size.
    array = new T[capacity]; //Array will point in the heap space to store an array of type T.
    for(int i = 0; i < size; i ++) //iteration through the array
    {
        array[i] = v.array[i]; //This will copy data elements over into the new array.
    }

};

template <typename T> //This is the copy assignment operator overload.
TVector<T> & TVector<T>::operator=(const TVector<T> & v)
{
    
    capacity = v.capacity; //This will copy the capacity;
    size = v.size;//This will copy the size.
    array = new T[capacity];
    for(int i = 0; i < size; i++)//This will interate through the array.
    {
        array[i] = v.array[i]; //This will copy data elements over.
    }

    return *this; //This returns the vector that has just been copy over.

};

template<typename T> //This is the move copy constructor.
TVector<T>::TVector(TVector<T> && v)
{
   
    
        capacity = v.capacity;
        size = v.size;
        array = v.array; //This will copy the pointee

        v.array = NULL; //rhs pointer will be set to nullptr.
        v.size = 0; //size will be 0.
        v.capacity = 0; //capacity will be 0.
    
};


template<typename T> //This is the move copy assignment operator overload.
TVector<T> & TVector<T>::operator=(TVector<T> && v)
{

    swap(array,v.array); //this will swap the pointers
    swap(capacity,v.capacity); //this will swap the capacity.
    swap(size,v.size); //this will swap the size.
    return *this;//return the calling object.

    //array pointer is now pointer to the RHS, it will be destroyed once the destructor is called.

};

template<typename T> //This is the function where it checks if the vector is empty
bool TVector<T>:: IsEmpty() const
{
    if(size == 0)
    {
        cout<<"Is empty!"<<endl;
        return true;
    }
    else 
    {
        cout<<"Not empty!"<<endl;
        return false;
    }   
};

template<typename T> //This is to clear the vector.
void TVector<T>::Clear()
{
    delete [] array; //this will delete the content.
    capacity = 0;
    size = 0; //chnage the size and capacity back to 0.

    array = new T[capacity+SPARECAPACITY]; //create a new array.

};

template<typename T> //This will get the current size of the vector.
int TVector<T>::GetSize() const
{
    return size;
};


template<typename T> //This will insert some data at the end of the vector.
void TVector<T>::InsertBack(const T & d)
{
    if(capacity == size) //This checks if the capacity is less than the size.
    {
        SetCapacity(size + 1 + SPARECAPACITY); //if so, I called this fucntion to increase the capacity.
    }

    array[size] = d; //this will insert the data element inside the at the current size(back of the vector).
    size = size + 1; //once inserted, I need to increase the size.
};

template<typename T>
void TVector<T>::RemoveBack()
{
    int * temp;

    temp = new T[capacity];

    for(int i = 0; i < size -1; i++) //make sure to go through all the elements until i reaches size -1.
    {
        temp[i] = array[i]; //copy the data members over.
    }
    size--;
    delete [] array; //delete all the content array is pointing to.

    array = temp; //now temp is being transfered to array.
};

template<typename T>
void TVector<T>::SetCapacity(unsigned int c)
{
    
    T *newArray = new T[c];
    for(int i = 0; i < size; i++)
    {
        newArray[i] = std::move(array[i]);
    }

    capacity = c;
    std::swap(array, newArray);
    delete [] newArray;
}; 

template <typename T>
void TVector<T>::Print(std::ostream& os, char delim) const
{
    for(int i = 0; i< size; i++)
    {
        os<<array[i]<<delim; //this will print out the current content of the array.
    }
};

template <typename T>
T& TVector<T>::GetFirst() const
{
    
        return array[0]; //returns the first element of the array.
    
};

template <typename T>
T& TVector<T>::GetLast() const
{
    return array[size - 1];//returns the last element of the array.
};


template<typename T>
TVectorIterator<T> TVector<T>::GetIterator() const
{

    TVectorIterator<T> itr;
    itr.index = 0;
    itr.vsize = size;
    itr.ptr = &array[0]; //this set the pointer to the address of the first element of my array pointer in my vector class


    return itr; //need to return itr.
};

template<typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const
{
    TVectorIterator<T> itr;

    itr.index = size-1;
    itr.vsize = size-1;
    itr.ptr = &array[size-1];

    return itr;
};
template<typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T&d)
{

        if((pos.index >= 0) && (pos.index <= size) )//need to check if index is within bounds.
        {
            if (size == capacity - 1) //Check if the size is equal to capacity.
            {
                SetCapacity(size + 1 + SPARECAPACITY); //if so, double the capacity plus one.
            }
            for (int i = size; i > pos.index; i--)
            {
                array[i] = array[i - 1]; //move elements to the right.
            }

            
            array[pos.index] = d; //indert data at the desired position.
            size = size + 1; //incremented size by one.
        } 
    
    pos.vsize = size;

    return pos;
 };   
template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos)
{
   
    
        for(int i = pos.index; i < size - 1; i++) //start from the index and end at size - 1
        {
            array[i] = array[i + 1]; //make sure that the elements move over to the left starting with the index
        }
        size--; //the size of the array will decrease by one.

        return pos; //this will return the iterator.
    
};

template<typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2)
{
    TVector<T> TempVector; //created a temp vector to store my concatenated vector;

    

    TVectorIterator<T> itr = t1.GetIterator(); //start iterator at the beginning.
	  
    for(int i = 0; i < t1.GetSize(); i++)
    {
        TempVector.InsertBack(itr.GetData());//thhis will insert the data into the back of the new array.
        itr = itr.Next(); //iterator will go to the next pos
    }

    itr = t2.GetIterator(); //same process here

    for(int i = 0; i < t2.GetSize(); i ++)
    {
        TempVector.InsertBack(itr.GetData());
        itr = itr.Next();
    }

    return TempVector; //need to return a iterator.
};


template <typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2)
{
    if(pos2.index > pos1.index)
    {
        for(unsigned int l = 0; l < pos2.index - pos1.index; l++) //This will loop based on the difference between pos1 and pos2.
        {
            for(unsigned int j = pos1.index; j < size - 1; j++) //This will shift the element to the right
            {
                array[j] = array[j + 1]; 
            }
            size--; //This will decrease the size once the elements have been shifted over.
        } 
        return pos2;
    }
    else if(pos2.index < pos1.index)
    {
        for(unsigned int l = 0; l <pos1.index - pos2.index; l++)
        {
            for(unsigned int j = pos2.index; j < size -1; j++)
            {
                array[j] = array[j+1];
            }
            size--;
            
        }

        return pos2;
    }
    else //If both pos1 and pos2 are at the same index it will return the original array;
    return pos2;
};

    		
 
///////////////TVectorIterator Class Implementations/////////////////////// ////////////////////
template<typename T>
TVectorIterator<T>::TVectorIterator()
{
    ptr = nullptr;
    vsize = 0;
};


template<typename T>
bool TVectorIterator<T>::HasNext() const
{
    if(vsize > index + 1) 
    {
        return true;
    }
    else
    return false;
};

template<typename T>
bool TVectorIterator<T>::HasPrevious() const

{
    if(vsize >= 1)
    {
        return true;
    }
    else
    return false;
};

template<typename T>
TVectorIterator<T> TVectorIterator<T>::Next()
{
       if(ptr != nullptr && HasNext())
       {
        index = index + 1;
        ptr = ptr + 1;
       }
       
        return *this;
};

template<typename T>
TVectorIterator<T> TVectorIterator<T>::Previous()
{
    if(ptr != nullptr && HasPrevious())
    {
        index = index - 1;
        ptr = ptr - 1;
    }

    return *this;
};

template<typename T>
T& TVectorIterator<T>::GetData() const
{
    
        return *ptr; //This will dereference the pointer at that current position.
};

#endif
