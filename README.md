# Basic idea

I want to practice my Japanese everyday. I want to make it easier to do. Also I want to structure all my doings.

---

# Start screen

There is app startscreen where shiuld be greeting. It should contain Japanese greeting words like:「おはよう、こんにちは、こんばんは」which will depend on current time and USERNAME.

 Also should be text: "Today score: USER_SCORE" like a subtitle

---

> ## Todo
> 
> - [x] Change database
> - [x] Add page
> - [x] Implement user data object

---

## Preview

<img alt="Preview" width="400" height="800" src="media/img/StartScreen.jpg">

# Cards

You can learn Kanji with card system. It was created for learning kanji. Card is square with rounded corners which contain some text. When user tap to card it will change content information.

If user get tired he can switch to Compare game which will do same concept, but in a game like mode.

> ## Todo
> 
> - [x] Card element
> - [x] Content switching
> - [x] Card disapearing
> - [x] Drag animation
> - [x] Connect score

---

## Database

Words table should contain
- word id
- Japanese kanji
- Russian translation
- Onyoumi and Kunyomi

```
create table if not exists Words (id INTEGER NOT NULL UNIQUE, ja TEXT NOT NULL, ru TEXT NOT NULL, pr TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT) )
```

---

## Card switching

For switching to next kanji drag animation was implemented. Now user can hold card and flip it to right or left side. Card will disapear and after new card with next kanji will appear.

| <img alt="Preview" src="media/img/DragAnimation.jpg"> | <img alt="Preview" src="media/img/DisapearAnimation.jpg"> |
| --- | --- |

---

# Progress

The progress system is essentially the number of points that are reset each day. When completing the exercise, for each completed task, the user receives a certain number of points. Progress should be categorized. Actions in the current category do not affect progress in others.

All this in the compartment must be synchronized with statistics on the server Sync

---

> ## Todo
>
> - [ ] Add scoring animation
> - [x] Add progressbar
> - [ ] Add effects

---

## Database


```
create table if not exists Stats (id INTEGER NOT NULL UNIQUE, date TEXT NOT NULL, score TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT))

create table if not exists User (id INTEGER NOT NULL UNIQUE, name TEXT NOT NULL, serverUri TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT))
```

- [x] Add table Stats
- [x] Add table User

## Interface

To indicate user progress is using standart progressbar in  [QtQuick.Controlls 2](https://doc.qt.io/qt-5/qml-qtquick-controls2-progressbar.html). It should be placed at the top of action page.

---

| <img alt="Preview" src="media/img/progress_showcase0.jpg"> | <img alt="Preview" src="media/img/progress_showcase1.jpg"> |
| --- | --- |

# Tests

The basic idea comes from original textbooks. There are a text with some word skips. User should fill this gaps correctly.

Most of the tests can be copied from original textbooks. It can be single sentense or large text.

For this activity I should create text formatter which will convert text with special tags to qml task. Programm should display text with tag corrections. Of the end of page will be placed comboboxes which will be connected with skiped words.

> ## Todo
> 
> - [x] Write concept
> - [x] Create table Tests

---

## Test example

Task is text with braces which will contain correct insertation.

私{は}猫{を}大好き。
Possible insertations: \[は,が,を,x\]

---

## Database

Table "Tetst" should contain
- id of a test
- test text
- possible insertations

```
create table if not exists Tests (id INT NOT NULL UNIQUE, content TEXT NOT NULL, insertations TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT))
```


# Training

Training is about compliting grammar tasks. Tasks can be profitably copied from books, as well as come up with unique ones. (TODO: see if the uchi.ru method is suitable in this case)
Most likely the main element of the tasks will be Combobox, Checkbox

> ## Todo
> 
> - [ ] Implement all activities

---

## Selection task

This page are simmillar with Tests. But instead of multiple selection it will be single. One question and multiple answers. User should choose correct answer for current task. 

> ## Todo
> 
> - [x] Create Selections database

---

## Interface

All content will be placed on long card. Question and answers will be separated by horizontal line. And it will be a submit button at right bottom corner. Also there should be some japanese backgrounds as option.

<img alt="Preview" src="media/img/Submit.png">