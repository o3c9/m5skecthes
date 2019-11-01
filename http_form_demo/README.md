# HTTP Form URL-encoded parameters with brackets

Parses the parameters with brackets using `WebServer` library

## Sample Request

```
curl -X "POST" "http://${IP}/post" \
     -H 'Content-Type: application/x-www-form-urlencoded; charset=utf-8' \
     --data-urlencode "names[0]=hanako" \
     --data-urlencode "values[0]=1" \
     --data-urlencode "names[1]=taro" \
     --data-urlencode "values[1]=4"
```
