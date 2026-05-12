#include <iostream>
#include <vector>
#include <string>
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

            if(largest < size && hasHighPriority(heap[left], heap[largest])) largest = left;
            if(largest < size && hasHighPriority(heap[right], heap[largest])) largest = right;
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


};






