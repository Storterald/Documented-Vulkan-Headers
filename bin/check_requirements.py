import importlib

if __name__ == "__main__":
        requirements: list = [ "bs4", "requests" ]
        for req in requirements:
                try:
                        importlib.import_module(req)
                except ImportError:
                        raise RuntimeError(f"Could not import {req}")
