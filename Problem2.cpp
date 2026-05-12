#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

struct Patient
{
    int id;
    string name;
    int severity;
    int arrivalTime;
};


class Heap {
    private:
        vector<Patient> heap;
        // helper functions for index calculations
        int parentIndex(int i) {
            return (i - 1) / 2;
        }

        int leftChildIndex(int i) {
            return 2 * i + 1;
        }

        int rightChildIndex(int i) {
            return 2 * i + 2;
        }

        // compare priority
        bool hasHighPriority(Patient a, Patient b) {

            if (a.severity > b.severity)
                return true;

            if (a.severity == b.severity &&
                a.arrivalTime < b.arrivalTime)
                return true;

            return false;
        }

        // heapify up
        void heapifyUp(int index){

            while (index > 0){

                int parent = parentIndex(index);

                if (hasHighPriority(heap[index], heap[parent]))
                {
                    swap(heap[index], heap[parent]);

                    index = parent;
                }
                else
                {
                    break;
                }
            }
        }

        // heapify down
        void heapifyDown(int index){
            int largest = index;
            int size = heap.size();
            int left = leftChildIndex(index);
            int right = rightChildIndex(index);

            if(left < size && hasHighPriority(heap[left], heap[largest])) largest = left;
            if(right < size && hasHighPriority(heap[right], heap[largest])) largest = right;
            if(largest != index){
                swap(heap[index], heap[largest]);
                heapifyDown(largest);
            }
        }

        public:
            int size(){
                return heap.size();
            }

            void insertPatient(Patient p){
                heap.push_back(p);
                heapifyUp(heap.size() - 1);
                cout << "New Patient: " << p.name << " (severity= " << p.severity << ", arrival= " << p.arrivalTime << ")" << "\n";
            }

            void treatPatient() {
                if(heap.empty()){
                    cout << "No Patients waiting\n";
                    return;
                }
                cout << "Treating patient " << heap[0].name << " | Severity: " << heap[0].severity << " | Arrival: "  << heap[0].arrivalTime << "\n";
                heap[0] = heap.back();
                heap.pop_back();
                if(!heap.empty()) heapifyDown(0);
            }

            void viewPatient(){
                if(heap.empty()){
                    cout << "No Patients\n";
                    return;
                }
                cout << "Next patient: " << heap[0].name << " | Severity: " << heap[0].severity << " | Arrival: "  << heap[0].arrivalTime << "\n";
            }
        
             void updateSeverity(int id, int newSeverity){ 
                for(int i = 0; i < heap.size(); i++){ 
                    if(heap[i].id == id){
                        int oldSeverity = heap[i].severity;
                        heap[i].severity = newSeverity;
                        cout << "Updated severity of patient " << heap[i].name << " from " << oldSeverity << " to " << newSeverity << "\n";
                        if(newSeverity > oldSeverity) heapifyUp(i);
                        else heapifyDown(i);
                        return;
                    }
                }
                cout << "Patient with ID " << id << " not found\n";
            }
            void displayAllPatients(){
                if(heap.empty()){
                    cout << "No Patients\n";
                    return;
                }
                cout << "All patients in waiting list:\n";
                for(const auto& patient : heap){
                    cout << "Patient: " << patient.name << " | Severity: " << patient.severity << " | Arrival: "  << patient.arrivalTime << "\n";
                }
            }
};
struct ComparePatients {
    bool operator()(Patient a, Patient b) {
        if(a.severity > b.severity) {
            return false;
        }
        if(a.severity < b.severity) {
            return true;
        }
        if(a.arrivalTime < b.arrivalTime) {
            return false;
        }
        return true;
    }
};

int main() {

    Heap hospital;

    hospital.displayAllPatients();//test when empty

    // insert 25 test patients
    hospital.insertPatient({1, "Ahmed", 8, 1});
    hospital.insertPatient({2, "Sara", 5, 2});
    hospital.insertPatient({3, "Omar", 9, 3});
    hospital.insertPatient({4, "Mona", 4, 4});
    hospital.insertPatient({5, "Youssef", 7, 5});
    hospital.insertPatient({6, "Laila", 10, 6});
    hospital.insertPatient({7, "Kareem", 6, 7});
    hospital.insertPatient({8, "Nour", 8, 8});
    hospital.insertPatient({9, "Hassan", 3, 9});
    hospital.insertPatient({10, "Mariam", 9, 10});
    hospital.insertPatient({11, "Adam", 2, 11});
    hospital.insertPatient({12, "Salma", 7, 12});
    hospital.insertPatient({13, "Ali", 5, 13});
    hospital.insertPatient({14, "Farah", 10, 14});
    hospital.insertPatient({15, "Ziad", 1, 15});
    hospital.insertPatient({16, "Rana", 8, 16});
    hospital.insertPatient({17, "Tamer", 6, 17});
    hospital.insertPatient({18, "Jana", 4, 18});
    hospital.insertPatient({19, "Mostafa", 9, 19});
    hospital.insertPatient({20, "Malak", 7, 20});
    hospital.insertPatient({21, "Nada", 3, 21});
    hospital.insertPatient({22, "Ibrahim", 10, 22});
    hospital.insertPatient({23, "Dina", 5, 23});
    hospital.insertPatient({24, "Mahmoud", 8, 24});
    hospital.insertPatient({25, "Reem", 6, 25});

    cout << "\n==DISPLAY ALL PATIENTS==\n";

    hospital.displayAllPatients();

    cout << "\n==VIEW NEXT PATIENT==\n";

    hospital.viewPatient();

    cout << "\n==UPDATE SEVERITY TESTS==\n";

    hospital.updateSeverity(2, 10);
    hospital.updateSeverity(15, 9);
    hospital.updateSeverity(9, 1);
    hospital.updateSeverity(100, 7);  // invalid ID test

    cout << "\n==VIEW NEXT PATIENT AFTER UPDATES==\n";

    hospital.viewPatient();

    cout << "\n==TREATING PATIENTS==\n";

    hospital.treatPatient();
    hospital.treatPatient();
    hospital.treatPatient();
    hospital.treatPatient();
    hospital.treatPatient();

    cout << "\n==REMAINING PATIENTS==\n";

    hospital.displayAllPatients();

    return 0;
}