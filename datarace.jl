using .Threads

function suma_desprotegida(n)
    arr = Int[]
    @threads for i in 1:n
        push!(arr, i)
        println("Soy el hilo: ", Threads.threadid(), " metiendo ", i)                    
    end
    println(arr)
    return sum(arr)
end

function suma_protegida(n)
    arr = Int[]
    lk = ReentrantLock()
    @threads for i in 1:n
        lock(lk) do 
            push!(arr, i)
            println("Soy el hilo: ", Threads.threadid(), " metiendo ", i)            
        end
    end
    println(arr)
    return sum(arr)
end