import gpt_2_simple as gpt2

model_name = "124M"

sess = gpt2.start_tf_sess()
gpt2.load_gpt2(sess, model_name=model_name)


text="The capital of France is"
summary = gpt2.generate(sess, model_name=model_name, prefix=text, length=4, return_as_list=True)[0]
print(summary)
