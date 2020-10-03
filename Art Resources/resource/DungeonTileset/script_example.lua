-- prints to stdout file ready to be `require`d in your game

local file = arg[1]

if not file then
  print("usage: lua " .. arg[0] .. " ./tiles_list")
  os.exit()
end

local data = {}
local fmt = '    %s = { x=%d, y=%d, w=%d, h=%d, animLen=%d, isAnim=%s },'
local tn = tonumber
local fp, err = io.open(arg[1], 'r')

if not fp then
  print(err)
  os.exit()
end

local pattern = '([a-z_]+)' .. (' ([0-9]+)'):rep(4) .. ' *([0-9+]?)'
for line in fp:lines() do
  --local name, x, y, w, h, anim_len = line:match('([a-z_]+)')
  local name, x, y, w, h, animLen = line:match(pattern)

  if name then
    data[#data+1] = fmt:format(
      name, tn(x), tn(y), tn(w), tn(h), tn(animLen == '' and 1 or animLen), animLen ~= '')
  end
end
fp:close()

table.sort(data)

io.write('return {\n', table.concat(data, '\n'), '\n}\n')
