/* ================= DNA BACKGROUND ANIMATION ================= */

const container = document.getElementById('canvas-container');

function createNode(delay) {
    const node = document.createElement('div');
    node.style.position = 'absolute';
    node.style.width = '8px';
    node.style.height = '8px';
    node.style.background = '#00f2ff';
    node.style.borderRadius = '50%';
    node.style.left = '50%';
    node.style.boxShadow = '0 0 10px #00f2ff';

    node.animate([
        { transform: `translate(-150px, 100vh) scale(0.5)`, opacity: 0 },
        { transform: `translate(150px, 50vh) scale(1)`, opacity: 0.8 },
        { transform: `translate(-150px, 0vh) scale(0.5)`, opacity: 0 }
    ], {
        duration: 8000,
        iterations: Infinity,
        delay: delay
    });

    container.appendChild(node);
}

// Double helix
for (let i = 0; i < 40; i++) {
    createNode(i * 200);
    createNode(i * 200 + 4000);
}

/* ================= ALIGNMENT BACKEND CALL ================= */

async function triggerAlignment() {

    const dna1 = document.getElementById("dna1").value.trim();
    const dna2 = document.getElementById("dna2").value.trim();

    if (!dna1 || !dna2) {
        alert("Please enter both DNA sequences.");
        return;
    }

    const payload = {
        dna1: dna1,
        dna2: dna2,
        match: parseInt(document.getElementById("match").value),
        mismatch: parseInt(document.getElementById("mismatch").value),
        gap: parseInt(document.getElementById("gap").value),
        choice: parseInt(document.getElementById("choice").value)
    };

    try {
        const response = await fetch("http://localhost:8000/align", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(payload)
        });

        if (!response.ok) {
            throw new Error("Backend error");
        }

        const result = await response.json();

        document.getElementById("resA").textContent = result.aligned_dna1;
        document.getElementById("resB").textContent = result.aligned_dna2;
        document.getElementById("scoreValue").textContent = result.score;

    } catch (err) {
        console.error(err);
        alert("Could not connect to backend. Is FastAPI running?");
    }
}
