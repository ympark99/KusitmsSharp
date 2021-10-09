/*

    1. 개발/기획에서 남자만 배치(1명씩 배치하며 요일이 같은사람 우선으로 2명)
    2. 디자인팀 요일 고려하여 배치
    3. 개발/기획 여자에서 팀에 할당된 인원 수와 요일을 고려하여 배치
    4. 팀별로 점수는 계산하고 있음(개발,기획,디자인 점수총합 / 인원)
    5. 팀별로 개발점수 총합을 비교해 가장 높은팀과 가장 낮은팀의 개발/기획 여자 swap
    (요일이 맞는 개발점수가 가장 높은 팀의 여자, 요일이 맞는 개발점수가 가장 낮은 팀의 LowScore 여자)
    6. 기획점수, 디자인 점수도 반복
    7. 팀별로 희망분야 count -> 겹치거나 없는 분야가 있으면 개발팀 여자 swap
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

vector<vector<string>> kustims_input; // 초기 input vector
vector<vector<string>> kustims_output; // 초기 input vector

int comp(vector<string> a, vector<string> b){
    return a.size() < b.size();
}

int daytoNum(string day){
    if(day == "월요일") return 0;
    else if(day == "화요일") return 1;
    else if(day == "수요일") return 2;
    else if(day == "목요일") return 3;
    else if(day == "금요일") return 4;
    else if(day == "일요일 오전") return 5;
    else if(day == "일요일 오후") return 6;
    else if(day == "일요일 저녁") return 7;
}

// 요일 고려해서 남자 배치
void selectManOrDesign(vector<vector<string>> people, bool isDesign){
    vector<vector<string>> manOrDesignDay(people.size());
    for(int i = 0; i< people.size(); i++){
        manOrDesignDay[i].push_back(people[i][0]); // manOrDesignDay 배열에 이름을 넣어줌
        istringstream ss(people[i][3]);
        string stringBuffer;
        // 가능 요일을 / 나눠서 string배열에 저장
        while (getline(ss, stringBuffer, '/')){
            manOrDesignDay[i].push_back(stringBuffer); // manOrDesignDay 배열에 요일별로 한칸씩 들어감
        }
    }

    sort(manOrDesignDay.begin(), manOrDesignDay.end(), comp); // 희망요일이 적은 순서대로 정렬

    for(int i = 0; manOrDesignDay.size(); i++){
        if(kustims_output[daytoNum(manOrDesignDay[i][1])].size() < 2 && !isDesign) // 두명 미만 일때만
            kustims_output[daytoNum(manOrDesignDay[i][1])].push_back(manOrDesignDay[i][0]); // 최종배열에 남자 배치
        else kustims_output[daytoNum(manOrDesignDay[i][1])].push_back(manOrDesignDay[i][0]); // 최종배열에 디자인 배치
    }
}

// 점수를 계산
void score(){
    -> 각각의 점수별로 소팅
    if(개발점수가 가장 높은 팀 - 개발점수가 가장 낮은 팀 < 5){
        swap(요일이 맞는 개발점수가 가장 높은 팀의 여자, 요일이 맞는 개발점수가 가장 낮은 팀의 LowScore 여자);
    }
    -> 기획, 디자인 점수도 반복
}

// 개발 분야 고려
void developField(){
    -> 팀별로 희망분야 count
    -> 없는 분야가 있거나 겹치는 분야가 3명 이상이면 개발팀 여자 swap
    -> 희망분야가 다 다르거나 2명 이하일때까지 반복
}

int main(void){
    vector<vector<string>> man; // 남자
    vector<vector<string>> design; // 디자인

    for(int i = 0; i< kustims_input.size(); i++){
        if(kustims_input[i][2] == "남") man.push_back(kustims_input[i]);
        if(kustims_input[i][1] == "디자인") design.push_back(kustims_input[i]);
    }
    selectManOrDesign(man, 0); // 개발 기획에서 남자만 배치

    selectManOrDesign(design, 1); // 디자인 요일 배치

    return 0;
}
