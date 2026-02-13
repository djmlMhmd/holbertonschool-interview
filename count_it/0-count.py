#!/usr/bin/python3
"""
Recursive function that queries the Reddit API and counts keyword occurrences
in hot article titles.
"""
import requests


def count_words(subreddit, word_list, after=None, word_counts=None,
                keywords=None, keyword_weights=None):
    """
    Recursively fetches hot articles from a subreddit and counts keyword occurrences
    in titles. Prints results sorted by count (desc) then alphabetically (asc).

    Args:
        subreddit: The subreddit name to query
        word_list: List of keywords to count (case-insensitive)
        after: Pagination token for Reddit API (internal use)
        word_counts: Accumulated counts across recursive calls (internal use)
        keywords: Set of lowercase keywords (internal use)
        keyword_weights: Multiplier per keyword for duplicates (internal use)
    """
    if word_counts is None:
        word_counts = {}
        keywords = set(w.lower() for w in word_list)
        keyword_weights = {}
        for w in word_list:
            kw = w.lower()
            keyword_weights[kw] = keyword_weights.get(kw, 0) + 1

    if not keywords:
        return

    url = f"https://www.reddit.com/r/{subreddit}/hot.json"
    headers = {"User-Agent": "python:count_it:v1.0 (by u/count_it)"}
    params = {"limit": 100}
    if after:
        params["after"] = after

    response = requests.get(
        url,
        headers=headers,
        params=params,
        allow_redirects=False,
        timeout=10,
    )

    if response.status_code != 200:
        return

    try:
        data = response.json()
    except ValueError:
        return

    children = data.get("data", {}).get("children", [])

    for post in children:
        title = post.get("data", {}).get("title", "")
        for word in title.split():
            w_lower = word.lower()
            if w_lower in keywords:
                word_counts[w_lower] = (word_counts.get(w_lower, 0) +
                                        keyword_weights[w_lower])

    after = data.get("data", {}).get("after")
    if after:
        count_words(subreddit, word_list, after=after, word_counts=word_counts,
                    keywords=keywords, keyword_weights=keyword_weights)
    else:
        sorted_items = sorted(
            word_counts.items(),
            key=lambda x: (-x[1], x[0])
        )
        for word, count in sorted_items:
            print(f"{word}: {count}")
