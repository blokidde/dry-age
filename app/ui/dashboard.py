from nicegui import ui

chart_options = {
    "title": {
        "text": "Temperature",
    },
    "tooltip": {
        "trigger": "axis",
    },
    "legend": {
        "data": ["Temperature", "relais"],
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
            "name": "relais",
            "type": "line",
            "data": [0, 1, 0, 1, 0],
        },
    ],
}

ui.label("Temperatuur en ijskast switch").classes("text-2xl font-bold")

ui.echart(chart_options).classes("w-full h-96")

chart_options = {
    "title": {
        "text": "humidity",
    },
    "tooltip": {
        "trigger": "axis",
    },
    "legend": {
        "data": ["Humidity", "atomizer"],
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
            "name": "Humidity",
            "type": "line",
            "data": [62.0, 61.5, 60.8, 60.2, 59.9],
        },
        {
            "name": "atomizer",
            "type": "line",
            "data": [0, 1, 0, 1, 0],
        },
    ],
}

ui.label("luchtvochtigheid en vernevelaar switch").classes("text-2xl font-bold")

ui.echart(chart_options).classes("w-full h-96")

chart_options = {
    "title": {
        "text": "speed in %",
    },
    "tooltip": {
        "trigger": "axis",
    },
    "legend": {
        "data": ["speed in %"],
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
            "name": "speed in %",
            "type": "line",
            "data": [22.8, 23.1, 23.4, 23.2, 23.0],
        },
    ],
}

ui.label("fan on").classes("text-2xl font-bold")

ui.echart(chart_options).classes("w-full h-96")

with ui.card().tight():
    with ui.card_section():
        ui.label('Lorem ipsum dolor sit amet, consectetur adipiscing elit, ...')

ui.run()