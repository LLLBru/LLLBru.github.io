#include <iostream>
#include <string>
using namespace std;

// ========== Sport 类 ==========
class Sport {
private:
    string name;
    string date;
    double timeLen;
    double calorie;
public:
    Sport() : name(""), date(""), timeLen(0), calorie(0) {}

    void setRecord(string n, string d, double t, double c) {
        name = n;
        date = d;
        timeLen = t;
        calorie = c;
    }

    void show() const {
        cout << "运动: " << name
             << " | 日期: " << date
             << " | 时长: " << timeLen << " 分钟"
             << " | 热量: " << calorie << " 千卡" << endl;
    }

    string getName()   const { return name; }
    string getDate()   const { return date; }
    double getTime()   const { return timeLen; }
    double getCalorie()const { return calorie; }
};

// ========== FitnessLog 类 ==========
class FitnessLog {
private:
    Sport records[50];
    int count;

    // 单位时间热量标准
    double calPerMinute(string name) {
        if (name == "跑步")   return 8.0;
        if (name == "跳绳")   return 10.0;
        if (name == "俯卧撑") return 6.0;
        if (name == "骑行")   return 5.0;
        return 0.0;
    }

public:
    FitnessLog() : count(0) {}

    void addRecord() {
        if (count >= 50) {
            cout << "记录已满，无法继续添加。\n";
            return;
        }

        int choice;
        string name;
        cout << "选择运动类型：1.跑步 2.跳绳 3.俯卧撑 4.骑行\n";
        cout << "请输入编号: ";
        cin >> choice;
        switch(choice) {
            case 1: name = "跑步"; break;
            case 2: name = "跳绳"; break;
            case 3: name = "俯卧撑"; break;
            case 4: name = "骑行"; break;
            default:
                cout << "无效的运动类型。\n";
                return;
        }

        string date;
        cout << "输入打卡日期 (格式 YYYY-MM-DD): ";
        cin >> date;

        double minutes;
        cout << "输入运动时长 (分钟): ";
        cin >> minutes;
        if (minutes <= 0) {
            cout << "时长必须为正数。\n";
            return;
        }

        double cal = calPerMinute(name) * minutes;
        records[count].setRecord(name, date, minutes, cal);
        count++;
        cout << "打卡成功！本次消耗 " << cal << " 千卡。\n";
    }

    void showAll() const {
        if (count == 0) {
            cout << "暂无打卡记录。\n";
            return;
        }
        cout << "\n========== 全部打卡记录 ==========\n";
        for (int i = 0; i < count; i++) {
            cout << "[" << i+1 << "] ";
            records[i].show();
        }
        cout << "==================================\n";
    }

    void showTotalStats() const {
        if (count == 0) {
            cout << "暂无数据可统计。\n";
            return;
        }
        double totalTime = 0, totalCal = 0;
        for (int i = 0; i < count; i++) {
            totalTime += records[i].getTime();
            totalCal += records[i].getCalorie();
        }
        cout << "\n===== 全部运动数据统计 =====\n";
        cout << "总记录数: " << count << endl;
        cout << "总运动时长: " << totalTime << " 分钟\n";
        cout << "总消耗热量: " << totalCal << " 千卡\n";
        cout << "============================\n";
    }

    void searchByDate() const {
        string date;
        cout << "请输入要查询的日期 (YYYY-MM-DD): ";
        cin >> date;
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (records[i].getDate() == date) {
                records[i].show();
                found = true;
            }
        }
        if (!found)
            cout << "未找到该日期的打卡记录。\n";
    }
};

// ========== 主函数 ==========
int main() {
    FitnessLog log;
    int choice;

    do {
        cout << "\n====== 健身运动打卡系统 ======\n";
        cout << "1. 添加运动打卡\n";
        cout << "2. 查看所有打卡记录\n";
        cout << "3. 运动数据统计（全部）\n";
        cout << "4. 按日期查询运动记录\n";
        cout << "5. 退出系统\n";
        cout << "请选择: ";
        cin >> choice;

        switch(choice) {
            case 1: log.addRecord();    break;
            case 2: log.showAll();      break;
            case 3: log.showTotalStats(); break;
            case 4: log.searchByDate(); break;
            case 5: cout << "再见！\n";  break;
            default: cout << "无效选项，请重试。\n";
        }
    } while (choice != 5);

    return 0;
}
