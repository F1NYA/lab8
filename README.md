## lab8

[![Travis-CI][travis-badge]][travis-builds]

[travis-badge]: https://travis-ci.org/F1NYA/lab8.svg?branch=master
[travis-builds]: https://travis-ci.org/F1NYA/lab8

Simple HTTP server + doxygen + travis-CI


1.<code>/</code> send JSON with server information: 
```json
{
    "title": "%SERVER_NAME%", 
    "developer": "%YOUR_NAME_SURNAME%", 
    "time": "%SERVER_TIME%"
}
```
2.<code>/favorites</code> send JSON-list of objects, indicating the list of favorite plants. Each such object must have several fields, among which there must be a numeric field <code>id</code> with a unique value for each object:
```json
[
  {
    "id": 1,
    "name": "Asparagus",
    "type": "Vegetable",
    "companions": ["Tomato", "Aster", "Dill"],
    "foes": ["Onion", "Garlic", "Potato"],
    "description": "Description..."
  },

  {
    "id": 2,
    "name": "Anise",
    "type": "Herb",
    "companions": ["Coriander", "Cilantro"],
    "foes": [],
    "description": "Description..."
  },
  
  ...
  
  {
    "id": 50,
    "name": "Watercress",
    "type": "Vegetable",
    "companions": ["Onion", "Chive", "Peppermint", "Spearmint"],
    "foes": [],
    "description": "Description..."
  }
]
```
3.<code>/favorites?{key}={value}</code> send JSON-sublist of objects from the list <code>/</code> favorites in which the <code>{key}</code> field has a value of <code>{value}</code>. The key <code>{key}</code>, which is filtering the list, is optional:
```json
http://localhost:8080/favorites?name=SummerSavory

{
    "id": 45,
    "name": "SummerSavory",
    "type": "Herb",
    "companions": ["Green Bean", "Onion"],
    "foes": [],
    "description": "Description..."
 }
 ```
4.<code>/favorites/{id}</code> send JSON object from the list <code>/</code> favorites by identifier with numeric value <code>{id}</code>. If an object with this value id was not found, return the HTTP status: <code>404 Not Found</code>.
```json
http://localhost:8080/favorites/12

{
    "id": 12,
    "name": "Celery",
    "type": "Vegetable",
    "companions": ["Cosmos", "Daisy", "SnapDragon"],
    "foes": ["Corn", "Aster"],
    "description": "Description..."
}
```
5.<code>/file</code> read the contents of the file <code>data.txt</code>, which is pre-placed in the data directory <code>/</code> project. Send a client JSON-object containing information about the name, size (in bytes) and text content of the file:
```json
{
    "filename": "%FILE_NAME%",
    "size": 1234,
    "content": "%FILE_CONTENT"
}
```
6.<code>/file/data</code> send JSON object with information about the number of all digits and letters in a file (file <code>data.txt</code>):
```json
{
    "letters": 1234,
    "digits": 4321
}
```
