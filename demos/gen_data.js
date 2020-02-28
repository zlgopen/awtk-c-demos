
const NR = 100;
for(let i = 0; i < NR; i++) {
  let t = i + 100;
  console.log(`static const char* item${i}_detail[] = {`);
  console.log(`  "文件号：${i}",`)
  console.log(`  "开始时间：2020-02-28 ${Math.round(t/60)} : ${Math.round(t%60)}",`)
  t+=10;
  console.log(`  "结束时间：2020-02-28 ${Math.round((t)/60)} : ${Math.round(t%60)}",`)
  console.log('NULL')
  console.log('};\n')

}

console.log("static item_info_t all_items[] = {");
for(let i = 0; i < NR; i++) {
  console.log(`  {"2020-02 ${i}", item${i}_detail},`);
}
console.log("};");
