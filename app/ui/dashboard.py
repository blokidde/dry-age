from nicegui import ui

from nicegui import ui


chart_options = {
    "title": {
        "text": "Temperature and humidity",
    },
    "tooltip": {
        "trigger": "axis",
    },
    "legend": {
        "data": ["Temperature", "Humidity"],
    },
    "xAxis": {
        "type": "category",
        "data": ["12:00", "12:05", "12:10", "12:15", "12:20"],
    },
    "yAxis": {
        "type": "value",
    },
    "series": [
        {
            "name": "Temperature",
            "type": "line",
            "data": [22.8, 23.1, 23.4, 23.2, 23.0],
        },
        {
            "name": "Humidity",
            "type": "line",
            "data": [62.0, 61.5, 60.8, 60.2, 59.9],
        },
    ],
}

ui.label("Droogkast Dashboard").classes("text-2xl font-bold")

ui.echart(chart_options).classes("w-full h-96")

with ui.card().tight():
    with ui.card_section():
        ui.label('Lorem ipsum dolor sit amet, consectetur adipiscing elit, ...')

ui.run()