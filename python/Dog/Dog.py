"""
The Dog class.

Presentation of basic class functionalities:
- Class attributes, without hiding them from the user and can be changed.
- Instance attributes.
- Method.

Presentation of basic skills:
- Input verification.
- Testing with manual result verification.
- Code block executed only when the module file is called directly.
"""


class Dog:
    # documentation written by chat gpt
    """
    A class representing a Dog with basic functionalities.

    Class Attributes:
    - bark_threshold (int): An age threshold to determine the type of bark.
    - bark_small (str): A string representing the bark for dogs below the threshold.
    - bark_big (str): A string representing the bark for dogs at or above the threshold.

    Methods:
    - __init__(self, name: str, age: int, weight: int): Initializes a Dog object with a name, age, and weight.
        Raises:
        - TypeError: If the 'name', 'age', or 'weight' parameters are not of the expected types.
        - ValueError: If the 'age' or 'weight' parameters are negative.

    - bark(self): Prints a bark message based on the dog's age and the bark threshold.

    Attributes:
    - name (str): The name of the dog.
    - age (int): The age of the dog.
    - weight (int): The weight of the dog.
    """

    bark_threshold: int = 7
    bark_small: str = 'bark, bark'
    bark_big: str = 'BARK, BARK'

    def __init__(self, name: str, age: int, weight: int):
        # documentation written by chat gpt
        """
        Initializes a Dog object.

        Parameters:
        - name (str): The name of the dog.
        - age (int): The age of the dog.
        - weight (int): The weight of the dog.

        Raises:
        - TypeError: If the 'name', 'age', or 'weight' parameters are not of the expected types.
        - ValueError: If the 'age' or 'weight' parameters are negative.
        """

        if type(name) is not str:
            raise TypeError(f"'name' parameter must be a string, not {type(name)}")
        if type(age) is not int:
            raise TypeError(f"'age' parameter must be a string, not {type(age)}")
        if age < 0:
            raise ValueError(f"'age' parameter must be non-negative")
        if type(weight) is not int:
            raise TypeError(f"'weight' parameter must be a string, not {type(weight)}")
        if weight < 0:
            raise ValueError(f"'weight' parameter must be non-negative")

        self.name = name
        self.age = age
        self.weight = weight

    def bark(self) -> None:
        # documentation written by chat gpt
        """
        Prints a bark message based on the dog's age and the bark threshold.
        """
        if self.age < Dog.bark_threshold:
            print(f'Dog {self.name} is barking: {Dog.bark_small}.')
        else:
            print(f'Dog {self.name} is barking: {Dog.bark_big}.')


def test_sunny_day_age_threshold_lower() -> None:
    # documentation written by chat gpt
    """
    Test function for a sunny day scenario with a lower age threshold.

    This function creates an instance of the Dog class with a specified name, age, and energy level.
    It then calls the `bark` method on the created Dog instance.

    Example:
    --------
    > test_sunny_day_age_threshold_lower()
    sunny day - age threshold, lower
    dog_1: Dog = Dog('name_1', 6, 1)
    dog_1.bark()

    Notes:
    ------
    - Ensure that the Dog class is defined before running this test.
    - The `bark` method is expected to print the barking behavior of the dog.
    """

    print('sunny day - age threshold, lower')

    # Creating an instance of the Dog class with a specified name, age, and weight  # <- written by chat gpt
    print("dog_1: Dog = Dog('name_1', 6, 1)")
    dog_1: Dog = Dog('name_1', 6, 1)

    # Calling the `bark` method on the created Dog instance  # <- written by chat gpt
    print('dog_1.bark()')
    dog_1.bark()


def test_sunny_day_age_threshold_higher():
    # documentation written by chat gpt
    """
    Test function for a sunny day scenario with a higher age threshold.

    This function creates an instance of the Dog class with a specified name, age, and energy level.
    It then calls the `bark` method on the created Dog instance.

    Example:
    --------
    > test_sunny_day_age_threshold_higher()
    sunny day - age threshold, higher
    dog_2: Dog = Dog('name_2', 7, 100)
    dog_2.bark()

    Notes:
    ------
    - Ensure that the Dog class is defined before running this test.
    - The `bark` method is expected to print the barking behavior of the dog.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None
    """

    print('sunny day - age threshold, higher')

    # Creating an instance of the Dog class with a specified name, age, and weight  # <- written by chat gpt
    print("dog_2: Dog = Dog('name_2', 7, 0)")
    dog_2: Dog = Dog('name_2', 7, 100)

    # Calling the `bark` method on the created Dog instance  # <- written by chat gpt
    print('dog_2.bark()')
    dog_2.bark()


def test_sunny_day_age_lowest():
    # documentation written by chat gpt
    """
    Test function for a sunny day scenario with the lowest age.

    This function creates an instance of the Dog class with a specified name, age, and energy level.
    It then calls the `bark` method on the created Dog instance.

    Example:
    --------
    > test_sunny_day_age_lowest()
    sunny day - age, lowest
    dog_3: Dog = Dog('name_3', 0, 0)
    dog_3.bark()

    Notes:
    ------
    - Ensure that the Dog class is defined before running this test.
    - The `bark` method is expected to print the barking behavior of the dog.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None
    """

    print('sunny day - age, lowest')

    # Creating an instance of the Dog class with a specified name, age, and weight  # <- written by chat gpt
    dog_3: Dog = Dog('name_3', 0, 0)

    # Calling the `bark` method on the created Dog instance  # <- written by chat gpt
    print('dog_3.bark()')
    dog_3.bark()


def test_rainy_day_name_wrong_type():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with the wrong type for the 'name' parameter.

    This function attempts to create an instance of the Dog class with an incorrect type for the 'name' parameter.
    It catches the TypeError that is expected to be raised and prints the error message.

    Example:
    --------
    > test_rainy_day_name_wrong_type()
    rainy day - name wrong type
    dog_e1: Dog = Dog(object(), 0, 0)
    error = TypeError('name must be a string')

    Notes:
    ------
    - Ensure that the Dog class is defined before running this test.
    - The 'name' parameter should be a string, and attempting to use a different type is expected to raise a TypeError.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None
    """

    print('rainy day - name wrong type')

    try:
        # Attempting to create an instance of the Dog class with an incorrect type for the 'name' parameter  # <- written by chat gpt
        print("dog_e1: Dog = Dog(object(), 0, 0)")
        dog_e1: Dog = Dog(object(), 0, 0)
    except TypeError as error:
        # Catching and printing the expected TypeError  # <- written by chat gpt
        print(f'{error = }')


def test_rainy_day_age_wrong_type():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with the wrong type for the 'age' parameter.

    This function attempts to create an instance of the Dog class with an incorrect type for the 'age' parameter.
    It catches the TypeError that is expected to be raised and prints the error message.

    Example:
    --------
    > test_rainy_age_wrong_type()
    rainy day - age wrong type
    dog_e2: Dog = Dog('name_e2', object(), 0)
    error = TypeError('age must be a non-negative integer')

    Notes:
    ------
    - Ensure that the Dog class is defined before running this test.
    - The 'age' parameter should be a non-negative integer, and attempting to use a different type is expected to raise a TypeError.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None
    """

    print('rainy day - age wrong type')

    try:
        # Attempting to create an instance of the Dog class with an incorrect type for the 'age' parameter  # <- written by chat gpt
        print("dog_e2: Dog = Dog('name_e2', object(), 0)")
        dog_e2: Dog = Dog('name_e2', object(), 0)
    except TypeError as error:
        # Catching and printing the expected TypeError  # <- written by chat gpt
        print(f'{error = }')


def test_rainy_day_age_wrong_value():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with an invalid value for the 'age' parameter.

    This function attempts to create an instance of the Dog class with a negative value for the 'age' parameter.
    It catches the ValueError that is expected to be raised and prints the error message.

    Example:
    --------
    > test_rainy_age_wrong_value()
    rainy day - age wrong value
    dog_e3: Dog = Dog('name_e3', -1, 0)
    error = ValueError('age must be a non-negative integer')

    Notes:
    ------
    - Ensure that the Dog class is defined before running this test.
    - The 'age' parameter should be a non-negative integer, and attempting to use a negative value is expected to raise a ValueError.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None
    """

    print('rainy day - age wrong value')

    try:
        # Attempting to create an instance of the Dog class with a negative value for the 'age' parameter  # <- written by chat gpt
        print("dog_e3: Dog = Dog('name_e3', -1, 0)")
        dog_e3: Dog = Dog('name_e3', -1, 0)
    except ValueError as error:
        # Catching and printing the expected ValueError  # <- written by chat gpt
        print(f'{error = }')


def test_rainy_day_weight_wrong_type():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with the wrong type for the 'weight' parameter.

    This function attempts to create an instance of the Dog class with an incorrect type for the 'weight' parameter.
    It catches the TypeError that is expected to be raised and prints the error message.

    Example:
    --------
    > test_rainy_weight_wrong_type()
    rainy day - weight wrong type
    dog_e4: Dog = Dog('name_e4', 0, object())
    error = TypeError('weight must be a non-negative float')

    Notes:
    ------
    - Ensure that the Dog class is defined before running this test.
    - The 'weight' parameter should be a non-negative float, and attempting to use a different type is expected to raise a TypeError.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None
    """

    print('rainy day - weight wrong type')

    try:
        # Attempting to create an instance of the Dog class with an incorrect type for the 'weight' parameter  # <- written by chat gpt
        print("dog_e4: Dog = Dog('name_e4', 0, object())")
        dog_e4: Dog = Dog('name_e4', 0, object())
    except TypeError as error:
        # Catching and printing the expected TypeError  # <- written by chat gpt
        print(f'{error = }')


def test_rainy_day_weight_wrong_value():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with an invalid value for the 'weight' parameter.

    This function attempts to create an instance of the Dog class with a negative value for the 'weight' parameter.
    It catches the ValueError that is expected to be raised and prints the error message.

    Example:
    --------
    > test_rainy_weight_wrong_value()
    rainy day - weight wrong value
    dog_e5: Dog = Dog('name_e5', 0, -1)
    error = ValueError('weight must be a non-negative float')

    Notes:
    ------
    - Ensure that the Dog class is defined before running this test.
    - The 'weight' parameter should be a non-negative float, and attempting to use a negative value is expected to raise a ValueError.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None
    """

    print('rainy day - weight wrong value')

    try:
        # Attempting to create an instance of the Dog class with a negative value for the 'weight' parameter  # <- written by chat gpt
        print("dog_e5: Dog = Dog('name_e5', 0, -1)")
        dog_e5: Dog = Dog('name_e5', 0, -1)
    except ValueError as error:
        # Catching and printing the expected ValueError  # <- written by chat gpt
        print(f'{error = }')


if __name__ == '__main__':

    test_sunny_day_age_threshold_lower(); print()
    test_sunny_day_age_threshold_higher(); print()
    test_sunny_day_age_lowest(); print()

    test_rainy_day_name_wrong_type(); print()
    test_rainy_day_age_wrong_type(); print()
    test_rainy_day_age_wrong_value(); print()
    test_rainy_day_weight_wrong_type(); print()
    test_rainy_day_weight_wrong_value()
