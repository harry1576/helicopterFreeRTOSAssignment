# Quick Tester for the logic used to reset the yaw slot count

TOTAL_SLOTS = 10
MAX_ABSOLUTE_ROTATIONS = 10

def round_yaw(current_yaw, target_yaw):
    if (abs(current_yaw) >= TOTAL_SLOTS * MAX_ABSOLUTE_ROTATIONS):
        target_yaw = target_yaw - current_yaw
        current_yaw = 0
        return (target_yaw, current_yaw)
    
    yaw_error = abs(current_yaw) % TOTAL_SLOTS
    yaw_change = 0
    if (yaw_error > (TOTAL_SLOTS / 2)):
        yaw_change = TOTAL_SLOTS - yaw_error
    else:
        yaw_change = 0 - yaw_error

    if (current_yaw < 0):
        yaw_change = 0 - yaw_change

    current_yaw += yaw_change 

    return (target_yaw, current_yaw)


def tests():
    yaws  = [(5000, 5050),(-5000, -5050), (100, 100), (-100, -110), (26, 30), (-26, -30)]
    answers = [(50, 0), (-50, 0), (0, 0), (-10, 0), (30, 30), (-30, -30)]
    results = []

    for yaw in yaws:
        ans = round_yaw(yaw[0], yaw[1])
        results.append(ans)
    
    if (answers != results):
        print("Failed")
    else:
        print("Passed")
        
    print("Answers: {}".format(answers))
    print("Results: {}".format(results))

tests()
