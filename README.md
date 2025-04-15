# Структура данных бинарные деревья + Акинатор

## Краткое описание
Моя реализация структуры данных бинарные деревья, хранящая в каждом узле 8 байт. А также реализована программа, похожая по сути на Акинатор по тематике One Piece.

## Описание бекэнда
В узле хранится 8 байт в поле node_data. Это решение обосновано тем, что таким образом в дереве можно хранить любой объект в виде адреса на него. Либо при желании изменить это поле и логику создания узлов.

```c
struct Node {

    int64_t node_data; // node data is 8 bytes
    Node* left_node;
    Node* right_node;
};
```

Вставка и замена узлов происходит путем передачи функции-компаратора в Insert_node и Replace_node соответственно. Также имеется функция Replace_node_auto для строк.
Данные в дерево можно передать из файла, а также после изменений дереве в этом же формате записать в другой файл.

<details>
<summary>Показать OnePiece_bin_tree.txt</summary>

```
{
    "Protagonist?"
    {
        "Shachibukai?"
        {
            "Yonko?"
            {
                "Admiral of the Navy?"
                {
                    "Works for the World Government?"
                    {
                        "Paramecia?"
                        {"Enel"}
                        {"Katakuri"}
                    }
                    {"Rob Lucci"}
                }
                {
                    "Former Admiral?"
                    {"Kizaru"}
                    {"Aokiji"}
                }
            }
            {
                "Zoan?"
                {
                    "Clown?"
                    {"Marshall D Teach"}
                    {"Buggy"}
                }
                {"Kaido"}
            }
        }
        {
            "Logia?"
            {"Doflamingo"}
            {"Crocodile"}
        }
    }
    {
        "From Mugiwara pirates?"
        {
            "Friend of King of the Pirates?"
            {
                "Swordsman?"
                {
                    "Woman?"
                    {"Eustass Kid"}
                    {
                        "Zoan?"
                        {"Boa Hancock"}
                        {"Yamato"}
                    }
                }
                {"Trafalgar Law"}
            }
            {
                "Yonko?"
                {"Rayleigh"}
                {"Shanks"}
            }
        }
        {
            "Woman?"
            {
                "Dead (Yo-ho-ho-ho-ho)?"
                {
                    "Devil fruit user?"
                    {
                        "Marimo?"
                        {"Sanji"}
                        {"Zoro"}
                    }
                    {"Luffy"}
                }
                {"Brook"}
            }
            {
                "Devil fruit user?"
                {"Nami"}
                {"Robin"}
            }
        }
    }
}
```
</details>

Имеется функция Output_node_definition, которая при нахождении элемента в дереве выводит описание объекта (по сути ответы на вопросы Акинатора)
Графический дебаг осуществляется с помощью graphviz.

## Пример дерева для Акинатора
![One Piece Akinator](other/OnePiece_graph.png)

Изображение добавляется в дерево только в случае, если png файл с таким узлом существует.
