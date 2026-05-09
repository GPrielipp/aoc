# Advent of Code 2025 DAY 5

input_ranges: list[list[int]] = []
cleaned_ranges: list[list[int]] = []


def add_range(input_range: list[int]) -> None:
    global cleaned_ranges
    i: int = 0
    if cleaned_ranges == []:
        cleaned_ranges.append(input_range)
    else:
        for cleaned_range in cleaned_ranges:
            i += 1
            if (  # If input starts within existing range
                input_range[0] >= cleaned_range[0]
                and input_range[0] <= cleaned_range[1]
            ):
                if input_range[1] <= cleaned_range[1]:
                    # Input is entirely within existing, ignore
                    break
                else:
                    # Input extends beyond end of existing, expand existing
                    cleaned_range[1] = input_range[1]
                    break
            elif (  # If input ends within existing range
                input_range[1] >= cleaned_range[0]
                and input_range[1] <= cleaned_range[1]
            ):
                # Input extends beyond beginning of existing, expand existing
                cleaned_range[0] = input_range[0]
                break
            elif (  # If input encompasses existing range
                input_range[0] < cleaned_range[0] and input_range[1] > cleaned_range[1]
            ):
                # Replace existing range
                cleaned_range[0] = input_range[0]
                cleaned_range[1] = input_range[1]
                break
            elif i == len(cleaned_ranges):
                cleaned_ranges.append(input_range)


def count_ranges(cleaned_ranges: list[list[int]]) -> int:
    running_total: int = 0

    for cleaned_range in cleaned_ranges:
        difference: int = cleaned_range[1] - cleaned_range[0] + 1
        running_total += difference

    return running_total


if __name__ == "__main__":
    with open("input", "r") as f:
        for line in f:
            if line.find("-") >= 0:
                split_range: list[int] = list(map(lambda x: int(x), line.split("-")))
                input_ranges.append(split_range)

    for input_range in sorted(input_ranges, key=lambda x: x[0]):
        add_range(input_range)

    print(f"Total fresh keys: {count_ranges(cleaned_ranges)}")
