using Distributed

function azarparalela(lanzamientos)
    numcaras = @distributed (+) for i = 1:lanzamientos
    Int(rand(Bool)) 
    end
    return numcaras
end

function azarnormal(lanzamientos) 
    numcaras = 0
    for i = 1:lanzamientos
        numcaras += Int(rand(Bool))
    end
    return numcaras
end 

numprocesos = Sys.CPU_THREADS
for proceso = 1:(numprocesos-1)
    print(proceso)
    addprocs(1)
    for i = 1:10
        @time azarparalela(10000000000)
    end
end

rmprocs(2:numprocesos)
