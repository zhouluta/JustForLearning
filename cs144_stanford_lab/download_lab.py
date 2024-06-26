import os

url = 'https://cs144.github.io/assignments/'
for i in range(0, 8):
    pdf_url = f"{url}check{i}.pdf"
    print(f"downloading pdf {str(i)}.")
    os.system(f"wget {pdf_url}")