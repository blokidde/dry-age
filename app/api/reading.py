from fastapi import FastAPI

app = FastAPI()

@app.get("/readings/latest/{sensor_id}/readings/latest")
async def read_latest(sensor_id: int):
    return {"sensor_id": sensor_id}