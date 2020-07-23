# Carpe Diem 
> A productivity journal app for the day.

### Group member information:
| Name                     | Email            |
| ------------------------ | ---------------- | 
| Naomi Hossain            | nhoss005@ucr.edu |
| Jamella Suzanne Pescasio | jpesc002@ucr.edu |
| Matthew Huang            | mhuan060@ucr.edu |

### What is Carpe Diem?
Carpe Diem is a **productivity journal app** for the day. It aims to keep the user focused on the present by limiting planning to one day and three categories, high priority, medium priority, and low priority.

Carpe Diem allows the user to **create a to-do list** for the day. Anything that has not been completed for the current day will be carried over the next day, though the user has the option to either keep past objectives or delete them.

### Why is it important and interesting?
This app keeps the user focused with what they need to do for the day. Instead of having a weekly planner or a monthly planner, the user is limited to a daily planner so that their focused on *one* thing, seizing the day. 

This app aims to limit procrastination by not allowing the user to plan ahead, only allowing them to focus on what needs to be done that day.

### What language/tools/technology do we plan to use?
Language:
- C++

Tools:
- Vim

### What will be the input/output of our project?
The input will be the objectives the user needs to complete in their to-do list. The output will be a to-do list featuring those objectives under their respective categories.

## Design Pattern Use
### Composite Pattern
**Problem:** We had two objects, `Tasks` and `Categories`, which we wanted to display to console. However, `Categories` can contain multiple `Tasks` and `Categories` which can contain more objects so accessing each individual object to display its information would not be ideal.

**Solution:** We worked with `Tasks` and `Categories` in the same interface to solve this problem. Now, `Categories` can display their information *and* the information of its children, whether it's a `Task` or a `Category`.

**Implementation:**

We used the following abstract base class (found in `base.hpp`) as an interface for `Tasks` and `Categories` to implement this solution.
```cpp
class Base {
    public:
        Base () { }

        virtual Base* at(int i) = 0;
        virtual bool is_complete() = 0;
        virtual void toggleComplete() = 0;
        virtual void display() = 0;
        virtual void setString(std::string src) = 0;
        virtual std::string getString() = 0;
        virtual void save(std::ofstream& out) = 0;
};
```
   
We developed the pure virtual functions with the following objectives.
- `at(int)`: Returns the child at the following index. If the object calling this function is a leaf node, such as a `Task` object, the function returns a `nullptr`.

- `is_complete()`: Returns a boolean value regarding the status of completion. `Tasks` have a private variable that shows their status of completion, with the initial state of `false`. If a `Category` object has children, each child `Task` calls this function and if at least one child returns false the function called by the `Category` object.

- `toggleComplete()`: Toggles the status of completion of the object that calls it. If the object's status of completion was `true`, it will be changed to `false` and vice versa. If the object has children, each child's status of completion will be toggled.

- `display()`: Outputs to console the names of each `Task` and `Category`. If a `Task` object calls the function, a string indicating its completion status will also be outputted ("[x]" for complete and "[ ]" for incomplete). If a `Category` object has children, each child `Task` calls this function and each child will be displayed in a numerical list.

- `setString(std::string)`: Modifies the name of the object calling it.

- `getString()`: Returns the name of the object calling it.

- `save(std::ofstream)`: Writes to file a tag which indicates the object's class (":task:" for `Task` and ":category:" for `Category`) and the object's name. If a `Task` object calls this function, an additional string is written to file which indicates the status of completion ("+" for complete and "-" for incomplete). If a `Category` object has children, each child `Task` calls this function.

We then developed the classes `Task` and `Category` which we needed to implement this design pattern.
- **Class** `Task`: This class represents the tasks in a to-do list and is the leaf node in a composite pattern. It has two private variables, a string representing its name and a boolean value representing its status of completion.

- **Class** `Category`: This class reprents the categories in a to-do list and is the composite/container in a composite pattern. It has two private variables, a string representing its name and a list of `Base*` objects representing its children, whether it's a `Task` object or another `Category` object. 

   This class also contains three additional functions to aid in its functionality of adding, removing, and accessing its children.

    - `add(Base*)`: Adds a `Base*` object to the `Category` object's list of children.
    
    - `remove(int)`: Removes a child in the `Category` object's list of children at the specified index.
    
    - `getSize()`: Returns the size of the `Category` object's list of children.

---

### Decorator Pattern
**Problem:** We wanted the user to be able to change the text to either be all in lowercase or all in uppercase depending on their preference at any given time. However, we needed it to be able to change `Categories` and `Task` objects without affecting their behavior at run-time. 

**Solution:** We decided to extend the interface, implementing a `Lower` and `Upper` class dynamically in order for the user to be able to decide whether they want to change the text to all lowercase or all uppercase.

**Implementation:**

We used the following abstract base decorator class (`baseDecorator.hpp`) which inherits from `base.hpp`. The baseDecorator is an interface for the `Lower` and `Upper` classes. 

```cpp
class BaseDecorator : public Base {
    private:
        Base* x;
    public:
        BaseDecorator(Base* src) { this->x = src; }
	
        virtual Base* at(int i) { return x->at(i); }
        virtual bool is_complete() { return x->is_complete(); }
        virtual void toggleComplete() { x->toggleComplete(); }
        virtual void display() { x->display(); }
	virtual void setString(std::string src) { x->setString(src); }
	virtual std::string getString() { return x->getString(); } 
	virtual void save(std::ofstream& out) { x->save(out); }
};
```

The `baseDecorator` class inherits all the pure virtual functions from the `base.hpp` class. We implemented two new classes that inherit from the `baseDecorator` class:
- **Class** `Lower`: This class will output a given string where all characters are in lowercase. It contains a private `Base*` variable and a display function. 

- **Class** `Upper`: This class will output a given string where all characters are in uppercase. It contains a private `Base*` variable and a display function.

    - `display()`: Both classes implement a display function inherited from the `baseDecorator.hpp` class. The function creates a copy of the string and converts all the characters into the desired style. 

---

### Visitor Pattern

## Class Diagrams
### Composite Pattern
![alt text](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/composite-pattern.png)

---

### Decorator Pattern
![alt text](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/Decorator-Pattern-Diagram.png)

---

### Visitor Pattern

## Input/Output
### Home Menu
> After running the app, following menu is printed in console.

From this menu, the user has seven options to choose from:
- **Input** `a`: Prompts the user to add a task in a specified category.

- **Input** `r`: Prompts the user to remove a task in a specified category.

- **Input** `e`: Prompts the user to edit a task in a specified category.

- **Input** `x`: Prompts the user to toggle a task as complete/incomplete in a specified category.

- **Input** `c`: Clears completed tasks from the to-do list.

- **Input** `s`: Outputs the current display settings to console and prompts the user with the option to change the display settings.

- **Input** `q`: Ends the program and saves any changes made to the to-do list and settings by writing them into a file specified by the program.

### Add Task - Input `a`
> After inputting `a`, the program prompts the user to add a task in a specified category.

### Remove Task - Input `r`
> After inputting `r`, the program prompts the user to remove a task in a specified category.

### Edit Task - Input `e`
> After inputting `e`, the program prompts the user to edit a task in a specified category.

### Toggle Complete/Incomplete - Input `x`
> After inputting `x`, the program prompts the user to toggle a task as complete/incomplete in a specified category.

### Clear Complete - Input `c`
> After inputting `c`, the program clears completed tasks from the to-do list.

### Settings - Input `s`
> After inputting `s`, the program outputs the current display settings to console and prompts the user with the option to change the display settings.

### Quit - Input `q`
> After inputting `q`, the program ends itself and saves any changes made to the to-do list and settings by writing them into a file specified by the program.

## How To Run the Code
> This app runs in a terminal, so the following lines of code will be done in command line.

Clone the repository:
```
$ git clone https://github.com/claynaut/final-project-nh-jp-mh.git
```
Compile the code (use `cmake3 .` if on `hammer`):
```
$ cmake .
$ make
```
Run the executable:
```
$ ./carpe_diem
```
