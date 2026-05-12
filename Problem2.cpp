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
        priority_queue <Patient,vector<Patient>, ComparePatients> pq;

        return 0;
    }






