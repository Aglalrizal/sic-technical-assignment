from flask import Flask
from flask import request

app = Flask(__name__)

data = [];

@app.route('/')
def index():
    return "Hello World!"
@app.route('/sensor-data', methods=['POST'])
def post():
    # temperature = request.args.get('temperature')
    # humidity = request.args.get('humidity')
    # # co2 = request.args.get('CO2')
    # # h2o = request.args.get('H2O')
    # # subData = [temperature, humidity]
    # subData = {"Temperature": temperature, "Humidity":humidity}
    # #subData = {"CO2": co2, "H2O":h2o}
    # data.append(subData)
    #print(f"Received temperature: {temperature}°C, humidity: {humidity}%")
    distance = request.args.get('distance')
    subData = {"Distance": distance}
    data.append(subData)
    print(f"Received distance: {distance}cm")
    return 'OK'

@app.route('/sensor-data', methods=['GET'])
def get():
    return data

if __name__ == '__main__':
    app.run(debug=True)