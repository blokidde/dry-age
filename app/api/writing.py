from fastapi import FastAPI

app = FastAPI()


@app.set("/")
async def read_item(item_id: int):
    return 0