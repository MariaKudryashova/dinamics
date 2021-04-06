# dinamics
Расчет фрактальной размерности аттрактора

### Содержание проекта

### Вариант 1. Полностью в python

cd dinprojects/dinamics/variant1/

requirements.txt - библиотеки для настройки окружения
config.py - параметры и настройки расчетов
mathportrait.py - функции
data.csv - исследуемый ряд чисел

Запуск:
env\Scripts\activate
python estimates.py

результаты:
dict_result.json



### Вариант 2. С помощью внешней библиотеки на C

!Внимание: параметры зашиты внутри С-библиотеки, надо будет переделать

Компиляция библиотеки
следует проверить наличие mingw и возможно что-то еще будет просить доустановить

запускаем виртуальное окружение из dinamics
env\Scripts\activate

заходим в variant2 и билдим внешнюю библиотеку
python setup.py build

в \build\lib.win-amd64-3.8 будет наш файл библиотечки с расширением pyd

работаем с расчетами
python api_estimates.py


### Вариант 3. Просто на C.

Расчет по скалярному временному ряду
компилируем
gcc estimate.c functions.c -o est

запускаем
est


### Вариант 4. Просто на C.

Расчет корреляционного интеграла и (в будущем) корреляционной размерности
входящих данных в виде векторов заданной размерности m

est_types.c - есть вопросы по типизации, отложено













Шпаргралка команд

Создать окружение и активировать его
python -m venv env
env\Scripts\activate
env\Scripts\deactivate

сделать список библиотек
pip freeze > requirements.txt

установить библиотеки
pip install -r requirements.txt



