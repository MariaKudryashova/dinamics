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



заходим в src и билдим внешнюю библиотеку
python setup.py build

имеем библиотечку с расширением "pyd" тут:
C:\Users\maru\pyprojects\c_libs\capi\build\lib.win-amd64-3.8

копируем ее себе в ресурсы и используем
через api_estimates.py













Шпаргралка команд

Создать окружение и активировать его
python -m venv env
env\Scripts\activate
env\Scripts\deactivate

сделать список библиотек
pip freeze > requirements.txt

установить библиотеки
pip install -r requirements.txt



