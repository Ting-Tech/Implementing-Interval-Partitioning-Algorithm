#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Lecture
{
    int start;
    int end;
};

bool compareLectures(const Lecture &a, const Lecture &b)
{
    return a.start < b.start;
}

map<int, vector<Lecture>> minClassrooms(vector<Lecture> &lectures)
{
    sort(lectures.begin(), lectures.end(), compareLectures);
    map<int, vector<Lecture>> classrooms; // Map to store lectures assigned to each classroom
    vector<int> endTimes;

    for (const auto &lecture : lectures)
    {
        bool scheduled = false;
        for (int i = 0; i < endTimes.size(); ++i)
        {
            if (endTimes[i] <= lecture.start)
            {
                endTimes[i] = lecture.end;
                classrooms[i].push_back(lecture); // Assign the lecture to this classroom
                scheduled = true;
                break;
            }
        }
        if (!scheduled)
        {
            endTimes.push_back(lecture.end);
            classrooms[endTimes.size() - 1].push_back(lecture); // Assign the lecture to a new classroom
        }
    }

    return classrooms;
}

int main()
{
    vector<Lecture> lectures = {
        {900, 1000}, {1100, 1600}, {1230, 1330}, {1030, 1600}, {930, 1400}, {1030, 1300}, {1130, 1530}, {1230, 1630}, {1100, 1200}, {930, 1400}, {1130, 1700}, {930, 1530}, {1200, 1730}, {1130, 1400}, {1230, 1500}, {1100, 1600}, {1200, 1700}, {1530, 1630}, {1630, 1730}, {900, 1600}};

    map<int, vector<Lecture>> classrooms = minClassrooms(lectures);
    cout << "所需的最少教室數量為：" << classrooms.size() << endl;

    // Output the lecture schedule for each classroom
    for (const auto &[classroom, assignedLectures] : classrooms)
    {
        cout << "教室 " << classroom + 1 << "：";
        for (const auto &lecture : assignedLectures)
        {
            cout << " Lecture(" << lecture.start << "-" << lecture.end << ")";
        }
        cout << endl;
    }

    return 0;
}