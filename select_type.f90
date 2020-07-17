type base
 integer :: ii
end type
type,extends(base) :: ext
 integer :: jj
end type
type xx
end type

class(base),allocatable :: aobj
allocate(ext::aobj)
 select type(sel=>aobj)
  class is(base)
   print*,"121"
  class is(base)
   print*,"121"
  typeis(integer)
   print*,"121"
  class default
   print*,"NG"
 end select
end
