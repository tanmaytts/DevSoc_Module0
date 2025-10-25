
from groq import Groq
import json

client = Groq(api_key="gsk_")

def ask_question(question):
    chat_completion = client.chat.completions.create(
        messages=[
            {"role": "user", "content": question}
        ],
        model="openai/gpt-oss-20b"
    )
    return chat_completion.choices[0].message.content

with open('text.txt', 'r') as file:
    questions = file.readlines()

responses = {}

for question in questions:
    question = question.strip()
    if question:
        print(f"Processing: {question}")
        answer = ask_question(question)
        responses[question] = answer

with open('responses.json', 'w') as json_file:
    json.dump(responses, json_file, indent=4)

print("\nAll responses saved to responses.json")