#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>



// Перечислимый тип для статуса задачи
enum class TaskStatus 
{
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks 
{
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const;

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const std::string& person);

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count);
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь.
void PrintTasksInfo(TasksInfo tasks_info) 
{
    std::cout << tasks_info[TaskStatus::NEW] << " new tasks"s
         << ", "s << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"s
         << ", "s << tasks_info[TaskStatus::TESTING] << " tasks are being tested"s
         << ", "s << tasks_info[TaskStatus::DONE] << " tasks are done"s << endl;
}

int main() 
{
    TeamTasks tasks;

    tasks.AddNewTask("Ilia"s);

    for (int i = 0; i < 3; ++i) 
    {
        tasks.AddNewTask("Ivan"s);
    }
    std::cout << "Ilia's tasks: "s;
    
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"s));
    std::cout << "Ivan's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"s));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 2);
    std::cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 2);
    std::cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);
}