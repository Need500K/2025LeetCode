import requests, random, json, os, time
from enum import Enum

class DifficultyEnum(Enum):
    EASY = "EASY"
    MEDIUM = "MEDIUM"
    HARD = "HARD"

# From Leetcode
def fetch_all_problems(difficulty:DifficultyEnum):
    url = "https://leetcode.com/graphql" 
    limit = 4000 # 한 번에 가져올 문제 수 
    query = """
    query problemsetQuestionList($categorySlug: String, $limit: Int, $skip: Int, $filters: QuestionListFilterInput) {
      problemsetQuestionList: questionList(
        categorySlug: $categorySlug
        limit: $limit
        skip: $skip
        filters: $filters
      ) {
        total: totalNum
        questions: data {
          acRate
          difficulty
          freqBar
          frontendQuestionId: questionFrontendId
          isFavor
          paidOnly: isPaidOnly
          status
          title
          titleSlug
          topicTags {
            name
            id
            slug
          }
          hasSolution
          hasVideoSolution
        }
      }
    }
    """
    
    variables = {
        "categorySlug": "algorithms",
        "skip": 0,
        "limit": limit,
        "filters": {
            "difficulty": difficulty.value
        }
    }
    
    payload = {
        "query": query,
        "variables": variables,
        "operationName": "problemsetQuestionList"
    }
    response = requests.post(url, json=payload)
        
    if response.status_code == 200:
        data = response.json()
        problems = data["data"]["problemsetQuestionList"]["questions"]
        return problems 
    else:
        print(f"Error {response.status_code}: {response.text}")
        return []
 
def get_random_problem(problems, solved_ids):
    today = time.strftime("%Y%m%d%H%M")
    random.seed(int(today))

    filtered_problems = [p for p in problems if p["frontendQuestionId"] not in solved_ids and p["paidOnly"]==False]
    if not filtered_problems:
        print("No available problems to select.")
        return None
    return random.choice(filtered_problems)

def save_previous_ids(solved_ids:list, new_id, filename:str):
    solved_ids.append(new_id)
    with open(filename, "w") as f:
        json.dump(solved_ids, f)

if __name__ == "__main__":
    # Load solved IDs
    record_file = "solved_ids.json"
    if os.path.exists(record_file):
        with open(record_file, "r") as f:
            solved_ids = json.load(f)
    else:
        solved_ids = []

    problems = fetch_all_problems(DifficultyEnum.HARD)
    if not problems:
        print("No problems fetched.")
        exit(1)
    
    random_problem = get_random_problem(problems, solved_ids)
    if not random_problem:
        exit(1)

    # Save new problem to issue.json
    issue = {
        "title": f"[LeetCode] {random_problem['frontendQuestionId']}: {random_problem['title']}",
        "body": f"https://leetcode.com/problems/{random_problem['titleSlug']}/"
    }
    with open("issue.json", "w") as f:
        json.dump(issue, f)
    
    # Update previous IDs
    save_previous_ids(solved_ids, random_problem["frontendQuestionId"], record_file)

    print(f"Issue data saved: {issue}")
