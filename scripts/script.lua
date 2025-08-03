function foo (a)
    print("foo", a)
    return coroutine.yield(2*a)
end



function test()

    co = coroutine.create(function (a,b)
        print("co-body", a, b)
        local r = foo(a+1)
        print("co-body", r)
        local r, s = coroutine.yield(a+b, a-b)
        print("co-body", r, s)
        return b, "end"
    end)

    print("lua coroutine function")
    print("main", coroutine.resume(co, 1, 10))
    print("main", coroutine.resume(co, "r"))
    print("main", coroutine.resume(co, "x", "y"))
    print("main", coroutine.resume(co, "x", "y"))
end

test()

function test1()
    print("hello, lua_function")
end


function test2()
    local i = 0
    repeat
        io.write(string.format("repeat times: %s\n", i))
        --io.write(table.concat({"repeat times: ", tostring(i), '\n'}))
        i = i + 1
        if i > 5 then
            break
        end
    until i > 10
end