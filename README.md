# dinamics
Calculation of the fractal dimension of the attractor

### Content

### V1. Python

cd dinprojects/dinamics/variant1/

requirements.txt 
config.py 
mathportrait.py
data.csv

Start:
env\Scripts\activate
python estimates.py

Results:
dict_result.json

### V2. With external library on C
mingw

1. Start dinamics env
env\Scripts\activate

3. Cd variant2
python setup.py build
result: \build\lib.win-amd64-3.8 library pyd

4. Start calculations
python api_estimates.py

### V3. Simple C
Compile
gcc estimate.c functions.c -o est
Start calculations
est

### V4. Simple C
Calculation a correlation integral and correlation dimention of input data 
(as a vectors of a given dimention m)

est_types.c - in progress now

### Commands

python -m venv env
env\Scripts\activate
env\Scripts\deactivate

pip freeze > requirements.txt

pip install -r requirements.txt



