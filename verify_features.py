import yaml
import jsonschema
import sys

def validate_yaml(schema_file, data_file):
    try:
        with open(schema_file, 'r') as f:
            schema = yaml.safe_load(f)
        
        with open(data_file, 'r') as f:
            data = yaml.safe_load(f)
            
        jsonschema.validate(instance=data, schema=schema)
        print(f"Verification successful: {data_file}")
        return True
    except jsonschema.exceptions.ValidationError as e:
        print(f"Verification failed: {data_file}")
        print(f"Error: {e.message}")
        print(f"Path: {' -> '.join(map(str, e.path))}")
        return False
    except Exception as e:
        print(f"An error occurred: {e}")
        return False

if __name__ == "__main__":
    schema_path = "features.schema.yaml"
    
    if len(sys.argv) < 2:
        print("Usage: python3 verify_features.py <data_file.yaml>")
        sys.exit(1)
        
    data_path = sys.argv[1]
    success = validate_yaml(schema_path, data_path)
    if not success:
        sys.exit(1)
