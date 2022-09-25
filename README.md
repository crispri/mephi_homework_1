Домашние задачи для курса МИФИ "Введение в программирование, часть 1".

## Клонируем репозиторий

```bash
# Переходим в директорию, где вы хотите разместить репозиторий с задачами.
# Например, `/home/<username>/mephi/programming-1` для Linux или `/Users/<username>/mephi/programming-1` для MacOS.
$ cd <выбранная директория>

# Клонируем свой репозиторий, который создается автоматически при регистрации на manytask.
# Имя репозитория доступно по ссылке "MY REPO" на mephi-dap.manytask.org.
$ git clone https://gitlab.manytask.org/mephi-dap-programming-1/students-2022/<ваш login с mephi-dap.manytask.org>.git

# Переходим в директорию склонированного репозитория.
$ cd <ваш репозиторий>

# Настраиваем свое имя в git.
$ git config --local user.name "<ваш login с mephi-dap.manytask.org>"
$ git config --local user.email "<ваш email с mephi-dap.manytask.org>"

# Настраиваем возможность получать обновления при появлении новых задач.
$ git remote add upstream https://gitlab.manytask.org/mephi-dap-programming-1/public-2022.git
```

## Подтягиваем новые задачи

Периодически необходимо подтягивать изменения из основного репозитория с задачками: https://gitlab.manytask.org/mephi-dap-programming-1/public-2022. Например, когда появляются новые задачки или меняются условия старых.

```bash
$ git pull upstream main
```

## Решаем задачи

В каждой из папок находится условие и файлы очередной задачи.

Файлы main.cpp и makefile в каждой задаче отвечают за тестирование. При проверке решения они перезаписываются, так что их изменения не учитываются.

Остальные файлы менять можно и нужно.

Для тестирования в каждой задаче достаточно вызвать:
```bash
$ make
```

Команда соберет бинарные файлы из исходных и запустит тесты в main.cpp.
