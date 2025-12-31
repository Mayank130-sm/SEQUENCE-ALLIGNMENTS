from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import subprocess
import os

app = FastAPI()

# Allow frontend access
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

class AlignRequest(BaseModel):
    dna1: str
    dna2: str
    gap: int
    match: int
    mismatch: int
    choice: int

@app.post("/align")
def align(req: AlignRequest):

    exe_path = os.path.join(os.getcwd(), "align.exe")

    try:
        result = subprocess.run(
            [
                exe_path,
                req.dna1,
                req.dna2,
                str(req.gap),
                str(req.match),
                str(req.mismatch),
                str(req.choice)
            ],
            capture_output=True,
            text=True,
            check=True
        )

        lines = result.stdout.strip().split("\n")

        if len(lines) < 3:
            raise RuntimeError("Invalid output from C++ program")

        return {
            "aligned_dna1": lines[0],
            "aligned_dna2": lines[1],
            "score": int(lines[2])
        }

    except Exception as e:
        return {
            "error": "Alignment failed",
            "details": str(e)
        }
