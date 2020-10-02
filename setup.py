import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="raytracer",
    version="0.0.1",
    author="Keane Quigley and Angus Stanton",
    author_email="keaneq@protonmail.com",
    description="Python object oriented ray tracer",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/kquigley29/ray-tracer",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_require=">=3.6",
)
