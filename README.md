# **APOO/C++ Project: Student - Enterprise Meetings Report**
## **Authors**
- **Name:** Viet HOANG  
- **Name:** Quang Ha TRAN 

## **Table of Contents**
1. [UML Class Diagram](#uml-class-diagram)
2. [Component Diagram](#component-diagram)
3. [Objectives](#objectives)
4. [Code Elements](#code-elements)
5. [Code Execution](#code-execution)
6. [Manual Adding](#manual-adding)

---

## **UML Class Diagram**

### **Explanation of Modeling Choices**

#### **1. Classes**
1.1 **Student Class**  
- Stores personal, educational, and professional details of a student.
- Handles both **first-cycle** and **second-cycle** student data accordingly.

1.2 **Degree and ProfessionalExperience Classes**  
- **Degree Class**: Represents academic achievements of students.  
- **ProfessionalExperience Class**: Captures work experience details.

1.3 **Enterprise Class**  
- Manages information about enterprises participating in meetings.

1.4 **Meeting Class**  
- Represents meetings involving students and enterprises.

1.5 **DataManager Class**  
- Acts as a **central controller** for managing objects like Students, Enterprises, and Meetings.  
- Handles operations such as adding, retrieving, and displaying data.

#### **2. Relationships**
- **Student - Degree**: Aggregation with * to * multiplicity (a student can have multiple degrees).  
- **Student - ProfessionalExperience**: Aggregation with 1 to * multiplicity (a student can have multiple experiences).  
- **Student - Meeting**: Association with 1 to 1..* multiplicity (a student can attend multiple meetings).  
- **Enterprise - Meeting**: Association with 1 to 1..* multiplicity (an enterprise can host multiple meetings).

---

## **Component Diagram**

- The **Component Diagram** illustrates the distribution of code across files and the relationships between them.  
- Highlights the use of libraries and dependencies.  

---

## **Objectives**

1. **Manage Entities**:
   - Efficiently add, store, and retrieve information about students, enterprises, and meetings.
2. **Ensure Data Integrity**:
   - Prevent duplication using unique identifiers.
   - Avoid scheduling conflicts for meetings.
3. **Provide Comprehensive Views**:
   - Display student CVs.
   - Show sorted meeting schedules.

---

## **Code Elements**

### **1. Algorithms**

#### **1.1 Detect Scheduling Conflicts**
- Checks for overlapping meetings for students or enterprises on the same date.  
- Iterates through existing meetings using conditional logic to identify conflicts.

#### **1.2 Sorting Method**
- Utilizes `std::sort()` to organize meetings:
  - **Meetings for a Student**: Sorted by date and time.  
  - **Meetings for Enterprises**: Sorted by enterprise name, then date and time.
- Combines `date` and `startTime` as a single string (`"YYYY-MM-DD HH:MM"`) for lexicographical sorting.

#### **1.3 Serialization and Deserialization**
- Allows loading data from files and saving new data into files:
  - **serialize()**: Converts an object to a string for storage.
  - **deserialize()**: Converts a string back into an object.
- Uses `stringstream` and delimiters (`|`) for structured parsing.

#### **1.4 Deserialization Validation**
- **Parsing**: Uses `getline` with a delimiter (`|`) to read data fields.  
- **Error Handling**: Wraps `stoi` calls in try-catch blocks to handle invalid inputs gracefully.

---

### **2. Implementation Choices**

#### **2.1 Use of Containers**
- **`std::vector`**:
  - Chosen for storing `Student`, `Enterprise`, and `Meeting` objects due to:
    - Dynamic resizing.
    - Efficient iteration for adding and accessing elements.
  - Alternatives like `std::list` or `std::set` were avoided due to limitations in random access and ordering.

#### **2.2 Modular Design**
- **DataManager Class**:
  - Acts as a central hub for managing collections and functionalities.
  - Handles operations such as displaying sorted lists and CVs.

---

## **Code Execution**

### **Steps to Run the Program**

1. **Compile the Code**:
   ```bash
   g++ DataManager.cpp Degree.cpp Enterprise.cpp Meeting.cpp ProfessionalExperience.cpp Student.cpp main.cpp -o main
   ```

2. **Run the Program**:
   ```bash
   ./main
   ```

### **File-Based Data Loading**

You can load data into the system by preparing input files:

#### **Example Files**

1. **students.txt**
   ```txt
   student_ID|first_name|last_name|address|phone_number|cycle|baccalaureates|year_obtained|place_obtained|DEGREES_START|degree_code, name, completion_year, completion_place|DEGREES_END|EXPERIENCE_START|exp_ID, company_name, position, start_date, end_date|EXPERIENCE_END
   ```

2. **enterprises.txt**
   ```txt
   enterprise_ID|name|address|contact_name|contact_number
   ```

3. **meetings.txt**
   ```txt
   meeting_ID|student_ID|enterprise_ID|date|start_time|end_time
   ```

### **Sample Outputs**

- **Display All Students**:
  Shows student details, including degrees and professional experiences.  

- **List Meetings for a Specific Student**:
  Displays meetings sorted by **date and time**.  

- **List Meetings for Enterprises**:
  Displays all meetings sorted by **enterprise name**, then **date and time**.

- **Display Student CV**:
  Prints a detailed CV of a specific student.

---

## **Manual Adding**

You can add data manually through the interactive menu:

1. **Adding a Student**:
   - Enter details such as name, ID, cycle, and educational/professional details.  
   - The program checks for duplicate IDs and prompts if necessary.

2. **Adding an Enterprise**:
   - Enter enterprise details such as name, address, and contact details.

3. **Scheduling a Meeting**:
   - Provide meeting details such as student ID, enterprise ID, date, and time.  
   - The program checks for scheduling conflicts.

4. **Saving Data**:
   - Use the "Save to File" option to persist new entries in their respective files.

---

## **Notes**

- **Data Integrity**:
  - Duplicate entries are prevented using unique identifiers for students, enterprises, and meetings.

- **Sorting**:
  - Ensures chronological ordering of meetings for both students and enterprises.

- **Error Handling**:
  - Handles invalid inputs during deserialization and runtime.

---
