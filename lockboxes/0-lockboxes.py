#!/usr/bin/python3
"""
Module that provides the canUnlockAll function to determine
if all boxes can be opened given their keys.
"""


def canUnlockAll(boxes):
    """
    Determines if all boxes can be opened.
    :param boxes: list of lists, each list contains keys inside a box
    :return: True if all boxes can be opened, else False
    """
    if not boxes or not isinstance(boxes, list):
        return False
    n = len(boxes)
    opened = set([0])
    keys = set(boxes[0])
    while keys:
        key = keys.pop()
        if 0 <= key < n and key not in opened:
            opened.add(key)
            keys.update(boxes[key])
    return len(opened) == n
